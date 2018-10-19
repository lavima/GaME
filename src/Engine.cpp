/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


Engine::Engine(Platform &platform, EngineConfig &config) {

    this->platform = &platform;
    this->config = &config;
    isRunning = false;
    game = NULL;
    scriptEnvironment = NULL;

}

void Engine::shutdown() {

    platform->Shutdown();

    std::vector<AddinContainer *>::iterator iter;
    for (iter = addins.begin(); iter != addins.end(); iter++) {

        platform->UnloadLibrary((*iter)->GetHandle());
        delete *iter;

    }

    xercesc::XMLPlatformUtils::Terminate();

    delete scriptEnvironment;

}

bool Engine::IsRunning() { return isRunning; }
ScriptEnvironment &Engine::GetScriptEnvironment() { return *scriptEnvironment; }
Platform &Engine::GetPlatform() { return *platform; }
Game *Engine::GetGame() { return game; }

void Engine::Initialize() {

    printf("Initiliazing engine\n");

    
    /* Retrieve the executable path from the command line */
    info.ExecutablePath = CommandLine::GetExecutablePath(GetCommandLineA());   
   

    scriptEnvironment = ScriptEnvironment::Create(*this);

    if (!platform->Initialize(config->GetPlatformConfig()))
        printf("WARNING: Failed to initialize the platform.\n");

    for (int i = 0; i < config->GetNumAddins(); i++)
        LoadAddin(config->GetAddin(i).GetSource());

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

void Engine::LoadGame(const string &filename) {

    game = Game::Load(filename);

    game->Initialize();

    isGameRunning = isRunning;
    while (isRunning && isGameRunning) {
        platform->HandleEvents();

        GameTime gameTime;

        if (game)
            game->Update(gameTime);

        for (EngineComponentMapIter iter = components.begin(); iter != components.end(); ++iter)
            iter->second->Update(gameTime);

        platform->SwapBuffers();
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

bool Engine::LoadAddin(const string &filename) {

    AddinContainer *addin = AddinContainer::Create(filename);
    AddinInfo info = addin->GetInfo();

    string libraryFilename = FilePath::GetFilename(filename);

    addin->SetHandle(platform->LoadLibrary(libraryFilename));
    if (!addin->GetHandle()) {
        printf("Failed to load the addin.\n");
        delete addin;
        return false;
    }

    void *address = platform->LoadLibrarySymbol(addin->GetHandle(), ADDIN_REGISTERADDIN);
    if (!address) {
        printf("Failed to load %s.\n", ADDIN_REGISTERADDIN);
        delete addin;
        return false;
    }

    addin->AddSymbol(ADDIN_REGISTERADDIN, address);

    RegisterAddinFun registerAddin = (RegisterAddinFun)address;
    registerAddin(info);

    if (info.GetType() == ENGINE_COMPONENT_ADDIN) {

        address = platform->LoadLibrarySymbol(addin->GetHandle(), ADDIN_CREATECOMPONENT);
        if (!address) {
            printf("Failed to load %s.\n", ADDIN_CREATECOMPONENT);
            delete addin;
            return false;
        }

        addin->AddSymbol(ADDIN_CREATECOMPONENT, address);

        for (auto iter = info.GetEngineComponents().begin(); iter != info.GetEngineComponents().end(); ++iter)
            EngineComponent::createEngineComponentMap.insert(CreateEngineComponentPair(iter->first, (CreateEngineComponentFun)address));

    }

    addins.push_back(addin);

    printf("Sucessfully loaded addin %s from %s\n", addin->GetInfo().GetName(), filename);

    return true;

}

void Engine::AddComponent(const string &typeName, const string &name) {

    if (components.find(name) != components.end())
        printf("The component with the specified name (%s) already exists\n", name.c_str());

    components[name] = EngineComponent::Create(*this, typeName, name);

}

void Engine::AddComponent(EngineComponent *component) {

    if (components.find(component->GetName()) != components.end())
        printf("The component with the specified name (%s) already exists\n", component->GetName());

    components[component->GetName()] = component;

}

EngineComponent *Engine::GetComponent(const string &name) {

    if (this->components.find(name) == this->components.end())
        return NULL;
    return this->components[name];

}

const string &Engine::GetCommandLine() { return platform->GetCommandLine(); }
const EngineInfo &Engine::GetInfo() { return (const EngineInfo &)info; }
