/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "lib/CStringHash.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "scripting/ScriptContext.h"
#include "scripting/Script.h"
#include "framework/GameTime.h"
#include "framework/GameComponent.h"
#include "framework/Game.h"
#include "AddinInfo.h"
#include "AddinContainer.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "Engine.h"


Engine *Engine::singleton = NULL;

Engine::Engine() {

  isRunning = false;
  game = NULL;
  scriptContext = NULL;

}

void Engine::shutdown() {

  PLATFORM->Shutdown();

  std::vector<AddinContainer *>::iterator iter;
  for (iter = addins.begin(); iter != addins.end(); iter++) {

    PLATFORM->UnloadLibrary((*iter)->GetHandle());
    delete *iter;

  }

  xercesc::XMLPlatformUtils::Terminate();

  delete scriptContext;

}

Engine *Engine::GetSingleton() {

  if (singleton == NULL)
    singleton = new Engine();  
  
  return singleton;

}

bool Engine::IsRunning() { return isRunning; }

ScriptContext *Engine::GetScriptContext() { return scriptContext; }

Game *Engine::GetGame() { return game; }

void Engine::Initialize(const char *filename) {

  printf("Initiliazing engine with %s\n", filename);

  engineConfig = EngineConfig::Load(filename);

  scriptContext = ScriptContext::Create();

  PlatformConfig *platformConfig = engineConfig->GetPlatformConfig();
  if (!platformConfig) 
    printf("WARNING: Missing valid platform configuration.\n");
  else if (!PLATFORM->Initialize(platformConfig))
    printf("WARNING: Failed to initialize the platform.\n");

  for (int i=0; i<engineConfig->GetNumAddins(); i++)
    LoadAddin(engineConfig->GetAddin(i)->GetSource());

  isRunning = true;

  /*
  Script *engineScript = Script::Create(scriptContext, filename);
  if (engineScript == NULL) {
    printf("Could not load the engine script.\n");
    return;
  }

  engineScript->Run();

  delete engineScript;
  */

}

void Engine::Stop() {

  if (!isRunning)
    printf("The engine is not running. It cannot be stopped.\n");
  isRunning = false;

}

void Engine::RunGame(const char *filename) {

  game = Game::Load(filename);

  game->Initialize();

  isGameRunning = isRunning;
  while (isRunning && isGameRunning) {
    PLATFORM->HandleEvents();

    GameTime gameTime;

    if (game)
      game->Update(&gameTime);

    PLATFORM->SwapBuffers();
  }
  
  if (!isRunning)
    shutdown();

}

void Engine::CloseGame() {

  if (!isGameRunning)
    printf("Unable to close game, since no game is currently running.\n");
  isGameRunning = true;

}

bool Engine::LoadAddin(const char *filename) {

  AddinContainer *addin = AddinContainer::Create(filename);
  AddinInfo *info = addin->GetInfo();

  char *libraryDirectory = dirname(strdup(filename));
  char *libraryFilename = new char[strlen(libraryDirectory) + strlen(info->GetLibraryFilename()) + 1];
  sprintf(libraryFilename, "%s/%s", libraryDirectory, info->GetLibraryFilename());

  addin->SetHandle(PLATFORM->LoadLibrary(libraryFilename));
  if (!addin->GetHandle()) {
    printf("Failed to load the addin.\n");
    delete addin;
    return false;
  }

  void *address = PLATFORM->LoadLibrarySymbol(addin->GetHandle(), ADDIN_REGISTERADDIN);
  if (!address) {
    printf("Failed to load %s.\n", ADDIN_REGISTERADDIN);
    delete addin;
    return false;
  }

  addin->AddSymbol(ADDIN_REGISTERADDIN, address);

  RegisterAddinFun registerAddin = (RegisterAddinFun)address;
  registerAddin(info);

  if (info->GetType() == GAME_COMPONENT_ADDIN) {

    address = PLATFORM->LoadLibrarySymbol(addin->GetHandle(), ADDIN_CREATECOMPONENT);
    if (!address) {
      printf("Failed to load %s.\n", ADDIN_CREATECOMPONENT);
      delete addin;
      return false;
    }

    addin->AddSymbol(ADDIN_CREATECOMPONENT, address);

    for (auto iter=info->GetGameComponentInfoBegin(); iter!=info->GetGameComponentInfoEnd(); ++iter)
      createGameComponentMap.insert(CreateGameComponentPair(iter->first, (CreateGameComponentFun)address));
    
  }

  addins.push_back(addin);

  printf("Sucessfully loaded addin %s from %s\n", addin->GetInfo()->GetName(), filename);

  return true;

}

GameComponent *Engine::CreateGameComponent(Game *game, const char *typeName, const char *name) {

  CreateGameComponentMapIter item = createGameComponentMap.find(typeName);
  if (item == createGameComponentMap.end()) {
    printf("Could not find the specified game component type %s\n", typeName);
    return NULL;
  }

  CreateGameComponentFun createGameComponent = createGameComponentMap[typeName];

  return createGameComponent(game, typeName, name);

}

