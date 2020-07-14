/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


Engine::Engine() : status_(EngineStatus::Created) {

    script_environment_ = nullptr;

    log_ = unique_ptr<Log>(new Log(cout));
    log_->AddOutputStream(cerr, EventType::Error);

}

bool Engine::Initialize() {

    if (CommandLine::HasOption("engineConfig")) {
        (*log_).AddEvent("Loading engine configuration from %s", CommandLine::GetOption("engineConfig").c_str());
        config_ = unique_ptr<EngineConfig>(Data::Load<EngineConfig>(CommandLine::GetOption("engineConfig")));
    } 
    else {
        (*log_).AddEvent("Loading default engine configuration");
        config_ = unique_ptr<EngineConfig>(Data::Load<EngineConfig>(DEFAULT_ENGINECONFIG_FILENAME));
    }

    if (!config_) {
        (*log_).AddEvent(EventType::Error, "No engine configuration loaded");
        return false;
    }

    if (CommandLine::HasOption("engineLogFilename"))
        config_->SetLogFilename(CommandLine::GetOption("engineLogFile"));
    
    log_file_ = unique_ptr<ofstream>(new ofstream(config_->GetLogFilename()));
    (*log_).AddOutputStream(*log_file_);
    
    (*log_).AddEvent("Initiliazing engine");

    info_.executablePath = CommandLine::GetProgram();   

    //script_environment_ = ScriptEnvironment::Create(*this);

    if (!config_->GetPlatformConfig()) {
        (*log_).AddEvent("Creating default platform config");
        config_->SetPlatformConfig(new DefaultPlatformConfig());
    }

    platform_ = unique_ptr<Platform>(Platform::Create(*this, *config_->GetPlatformConfig()));

    if (!platform_->Initialize()) {
        (*log_).AddEvent(EventType::Error, "Platform failed to initialize. Can't initialize engine.");
        return false;
    }

    (*log_).AddEvent(EventType::All, "Loading addins");
    for (const string& addin_filename:config_->GetAddinFilenames()) {
        if (!LoadAddin(addin_filename)) {
            (*log_).AddEvent(EventType::Error, "Failed to load addin %s", addin_filename);
            return false;
        }

    }

    return true;

    /*
    Script *engineScript = Script::Create(scriptContext, filename_);
    if (engineScript == NULL) {
      printf("Could not load the engine_ script.\n");
      return;
    }

    engineScript->Start();

    delete engineScript;
    */

}

void Engine::Run() {

    if (!game_) {
        log_->AddEvent("Nothing to run. Returning");
        return;
    }

    for (pair<string, EngineComponent*> component_pair:components_) {

        log_->AddEvent("Initializing engine component %s", component_pair.first);
        if (!component_pair.second->Initialize()) {
            log_->AddEvent(EventType::Error, "Couldn't initialize engine component %s", component_pair.first);
            return;
        }

    }
        

    log_->AddEvent("Starting game");
    if (!game_->Start()) {
        log_->AddEvent("Failed to start game. Returning");
        return;
    }
    
    while (game_->GetStatus() == GameStatus::Running) {
        platform_->HandleEvents();

        GameTime gameTime;

        if (game_)
            game_->Update(gameTime);

        for (unordered_map<string, EngineComponent*>::iterator iter = components_.begin(); iter!=components_.end(); ++iter)
            iter->second->Update(gameTime);

        platform_->SwapBuffers();
    }

}

void Engine::Stop() {

    if (!game_) {
        log_->AddEvent(EventType::Info, "No game is currently running.");
        return;
    }

    game_->Stop();

}

bool Engine::LoadGame(const string &filename) {

    GameSpecification* game_spec = Data::Load<GameSpecification>(filename);
    if (!game_spec) {
        log_->AddEvent(EventType::Error, "Failed to load game specification from %s", filename);
        return false;
    }    

    game_ = unique_ptr<Game>(new Game(game_spec));

    if (!game_->Initialize(*this)) {
        log_->AddEvent(EventType::Error, "Failed to initialize game");
        return false;
    }

    log_->AddEvent("Game %s loaded and initialized", (const string&)game_->GetHeader().GetName());

    return true;

}

void Engine::UnloadGame() {

    if (!game_) {
        log_->AddEvent(EventType::Info, "No game is currently running.");
        return;
    }

    game_->UnloadContent();

}

bool Engine::LoadAddin(const string &filename) {

    Addin *addin = Addin::Load(*this, filename);
    if (!addin)
        return false;

    addins_.push_back(addin);

    // If the engine_ has already been initialized, we should add the addin filename
    // to the engine_ configuration
    if (status_ > EngineStatus::Created)
        config_->AddAddinFilename(filename);

    log_->AddEvent("Sucessfully loaded addin %s from %s\n", addin->GetHeader().GetName().c_str(), filename.c_str());

    return true;

}

bool Engine::HasComponentType(const string& type_name) const {

    bool found = false;

    for (Addin* addin:addins_) {
        
        for (const EngineComponentVersionInfo& component_info:addin->GetHeader().GetEngineComponents()) {
    
            if (component_info.GetName()==type_name) {
                found = true;
                break;
            }
        }
        
        if (found)
            break;
    }

    return found;

}

//void Engine::AddComponent(const string &name, const string &type_name) {
//
//    if (components_.find(type_name) != components_.end())
//        printf("The component with the specified name (%s) already exists\n", type_name.c_str());
//
//    components_[type_name] = EngineComponent::Create(*this, new EngineComponentConfig(name, type_name));
//
//}

void Engine::AddComponent(EngineComponentConfig& config) {

    if (components_.find(config.GetTypeName()) != components_.end())
        printf("The component with the specified name (%s) already exists\n", config.GetTypeName().c_str());

    components_[config.GetTypeName()] = EngineComponent::Create(*this, config);

}

EngineComponent *Engine::GetComponent(const string &name) {

    if (this->components_.find(name) == this->components_.end())
        return NULL;
    return this->components_[name];

}

ScriptEnvironment &Engine::GetScriptEnvironment() { return *script_environment_; }
Platform &Engine::GetPlatform() { return *platform_; }
Game &Engine::GetGame() { return *game_; }

const EngineInfo &Engine::GetInfo() { return (const EngineInfo &)info_; }

Log &Engine::GetLog() { return *log_; }

void Engine::shutdown() {

    platform_->Shutdown();

    std::vector<Addin *>::iterator iter;
    for (iter = addins_.begin(); iter != addins_.end(); iter++) {

        platform_->UnloadLibrary((*iter)->GetHandle());
        delete *iter;

    }

    delete script_environment_;

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

    //(*(*environment.GetContext())->Global)->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "engine_", v8::NewStringType::kNormal).ToLocalChecked(), engine_);

}
