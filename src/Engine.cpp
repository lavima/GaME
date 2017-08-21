/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>
#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "lib/CStringHash.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "scripting/ScriptEnvironment.h"
#include "scripting/Script.h"
#include "framework/GameTime.h"
#include "framework/Game.h"
#include "AddinInfo.h"
#include "AddinContainer.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "EngineComponent.h"
#include "Engine.h"


Engine *Engine::singleton = NULL;

Engine::Engine() {

  isRunning = false;
  game = NULL;
  scriptEnvironment = NULL;

}

void Engine::shutdown() {

  PLATFORM->Shutdown();

  std::vector<AddinContainer *>::iterator iter;
  for (iter = addins.begin(); iter != addins.end(); iter++) {

    PLATFORM->UnloadLibrary((*iter)->GetHandle());
    delete *iter;

  }

  xercesc::XMLPlatformUtils::Terminate();

  delete scriptEnvironment;

}

Engine *Engine::GetSingleton() {

  if (singleton == NULL)
    singleton = new Engine();  
  
  return singleton;

}

bool Engine::IsRunning() { return isRunning; }
ScriptEnvironment *Engine::GetScriptEnvironment() { return scriptEnvironment; }
Game *Engine::GetGame() { return game; }

void Engine::Initialize(const char *filename) {

  printf("Initiliazing engine with %s\n", filename);

  engineConfig = EngineConfig::Load(filename);

  scriptEnvironment = ScriptEnvironment::Create(this);

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

void Engine::LoadGame(const char *filename) {

  game = Game::Load(filename);

  game->Initialize();

  isGameRunning = isRunning;
  while (isRunning && isGameRunning) {
    PLATFORM->HandleEvents();

    GameTime gameTime;

    if (game)
      game->Update(&gameTime);

    for (EngineComponentMapIter iter=components.begin(); iter!=components.end(); ++iter)
      iter->second->Update(&gameTime);

    PLATFORM->SwapBuffers();
  }
  
  if (!isRunning)
    shutdown();

}

void Engine::CloseGame() {

  if (!isGameRunning) {
    printf("Unable to close game, since no game is currently running.\n");
    return;
  }
  isGameRunning = false;

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

  if (info->GetType() == ENGINE_COMPONENT_ADDIN) {

    address = PLATFORM->LoadLibrarySymbol(addin->GetHandle(), ADDIN_CREATECOMPONENT);
    if (!address) {
      printf("Failed to load %s.\n", ADDIN_CREATECOMPONENT);
      delete addin;
      return false;
    }

    addin->AddSymbol(ADDIN_CREATECOMPONENT, address);

    for (auto iter=info->GetEngineComponentInfoBegin(); iter!=info->GetEngineComponentInfoEnd(); ++iter)
      EngineComponent::createEngineComponentMap.insert(CreateEngineComponentPair(iter->first, (CreateEngineComponentFun)address));
    
  }

  addins.push_back(addin);

  printf("Sucessfully loaded addin %s from %s\n", addin->GetInfo()->GetName(), filename);

  return true;

}

void Engine::AddComponent(const char *typeName, const char *name) {

  if (components.find(name) != components.end())
    printf("The component with the specified name (%s) already exists\n", name);

  components[name] = EngineComponent::Create(typeName, name);
  
}

void Engine::AddComponent(EngineComponent *component) {
  
  if (components.find(component->GetName()) != components.end())
    printf("The component with the specified name (%s) already exists\n", component->GetName());

  components[component->GetName()] = component;

}

EngineComponent *Engine::GetComponent(const char *name) { 

  if (this->components.find(name) == this->components.end())
    return NULL;
  return this->components[name];

}
