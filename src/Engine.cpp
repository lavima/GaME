/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


Engine::Engine(Platform &platform, const string &configFilename) : Engine(platform, new EngineConfig(configFilename)) {}

Engine::Engine(Platform &platform, EngineConfig *engineConfig) {

    this->platform = &platform;
    this->config = engineConfig;

    isRunning = false;
    game = nullptr;
    scriptEnvironment = nullptr;

    log = new Log(config->GetLogFilename());

}

void Engine::Initialize() {

    printf("Initiliazing engine\n");
    
    /* Retrieve the executable path from the command line */
    info.executablePath = string(CommandLine::GetExecutablePath(platform->GetCommandLine()));   

    scriptEnvironment = ScriptEnvironment::Create(*this);

    if (!platform->Initialize())
        printf("WARNING: Failed to initialize the platform.\n");

    for (vector<string>::const_iterator iter = config->GetAddinFilenames().begin(); iter != config->GetAddinFilenames().end(); ++iter)
        LoadAddin(*iter);

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

    game->Initialize(*this);

    isGameRunning = isRunning;
    while (isRunning && isGameRunning) {
        platform->HandleEvents();

        GameTime gameTime;

        if (game)
            game->Update(gameTime);

        for (unordered_map<string, EngineComponent *>::iterator iter = components.begin(); iter != components.end(); ++iter)
            iter->second->Update(gameTime);

        platform->SwapBuffers();
    }

    if (!isRunning)
        shutdown();

}

void Engine::CloseGame() {

    if (!isGameRunning) {
        printf("No game is currently running.\n");
        return;
    }
    isGameRunning = false;

}

bool Engine::LoadAddin(const string &filename) {

    

    Addin *addin = Addin::Load(filename);
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
            EngineComponent::createEngineComponentMap.insert(pair<string, CreateEngineComponentFun>(iter->first, (CreateEngineComponentFun)address));

    }

    addins.push_back(addin);

    config->AddAddinFilename(filename);

    printf("Sucessfully loaded addin %s from %s\n", addin->GetInfo().GetName().c_str(), filename.c_str());

    return true;

}

void Engine::AddComponent(const string &typeName, const string &name) {

    if (components.find(name) != components.end())
        printf("The component with the specified name (%s) already exists\n", name.c_str());

    components[name] = EngineComponent::Create(*this, name, name);

}

void Engine::AddComponent(EngineComponent *component) {

    if (components.find(component->GetTypeName()) != components.end())
        printf("The component with the specified name (%s) already exists\n", component->GetTypeName().c_str());

    components[component->GetTypeName()] = component;

}

EngineComponent *Engine::GetComponent(const string &name) {

    if (this->components.find(name) == this->components.end())
        return NULL;
    return this->components[name];

}

bool Engine::IsRunning() { return isRunning; }
ScriptEnvironment &Engine::GetScriptEnvironment() { return *scriptEnvironment; }
Platform &Engine::GetPlatform() { return *platform; }
Game &Engine::GetGame() { return *game; }

const string &Engine::GetCommandLine() { return platform->GetCommandLine(); }
const EngineInfo &Engine::GetInfo() { return (const EngineInfo &)info; }

Log &Engine::GetLog() { return *log; }

void Engine::shutdown() {

    platform->Shutdown();

    std::vector<Addin *>::iterator iter;
    for (iter = addins.begin(); iter != addins.end(); iter++) {

        platform->UnloadLibrary((*iter)->GetHandle());
        delete *iter;

    }

    delete scriptEnvironment;

}

void scriptableLoadAddin(const v8::FunctionCallbackInfo<v8::Value>& args) {

    v8::Local<v8::Object> self = args.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

    Engine *engine = (Engine *)wrap->Value();
    v8::String::Utf8Value filename(args.GetIsolate(), args[0]);
    engine->LoadAddin(*filename);

}

void scriptableLoadGame(const v8::FunctionCallbackInfo<v8::Value>& args) {

    v8::Local<v8::Object> self = args.Holder();
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

    Engine *engine = (Engine *)wrap->Value();
    v8::String::Utf8Value filename(args.GetIsolate(), args[0]);
    engine->LoadGame(*filename);

}
void Engine::Scriptable::Register(ScriptEnvironment &environment) { 
    
    _Scriptable::Register(environment);

    v8::Handle<v8::ObjectTemplate> engine = v8::ObjectTemplate::New(environment.GetIsolate());
    engine->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "loadGame", v8::NewStringType::kNormal).ToLocalChecked(),
            v8::FunctionTemplate::New(environment.GetIsolate(), scriptableLoadGame));
    engine->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "loadAddin", v8::NewStringType::kNormal).ToLocalChecked(),
            v8::FunctionTemplate::New(environment.GetIsolate(), scriptableLoadAddin));

    //(*(*environment.GetContext())->Global)->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "engine", v8::NewStringType::kNormal).ToLocalChecked(), engine);

}
