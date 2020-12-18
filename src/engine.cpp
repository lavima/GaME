/*
File: Engine.cpp
Author: Lars Vidar Magnusson
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <pugixml.hpp>
#include <v8.h>

#include "global.h"
#include "lib/file_path.h"
#include "lib/format.h"
#include "lib/command_line.h"
#include "content/xml/xml_range.h"
#include "content/xml/xml_attribute.h"
#include "content/xml/xml_node.h"
#include "content/xml/xml_document.h"
#include "content/xml/xml_serializable.h"
#include "content/content.h"
#include "content/xml_content.h"
#include "version.h"
#include "version_info.h"
#include "scripting/script_environment.h"
#include "scripting/script.h"
#include "scripting/scriptable.h"
#include "platform/input_key.h"
#include "platform/platform_config.h"
#include "platform/platform.h"
#include "platform/glfw_vulkan_config.h"
#include "platform/default_platform.h"
#include "framework/framework.h"
#include "framework/system_info.h"
#include "framework/game_time.h"
#include "framework/system_config.h"
#include "framework/component_config.h"
#include "framework/component.h"
#include "framework/entity_specification.h"
#include "framework/entity.h"
#include "framework/game_header.h"
#include "framework/game_config.h"
#include "framework/game_specification.h"
#include "framework/game.h"
#include "framework/system.h"
#include "framework/component_info.h"
#include "addin/system_provider.h"
#include "addin/addin_header.h"
#include "addin/addin.h"
#include "log.h"
#include "engine_config.h"
#include "engine.h"

namespace game {

    Engine::Engine() : status_(EngineStatus::Created) {
				
        script_environment_ = nullptr;

        log_ = &Log::Get();
        //Log::Get().AddOutputStream(std::cerr);

    }

    Engine::~Engine() {}

    bool Engine::Initialize() {
        if (lib::CommandLine::HasOption("engineConfig")) {
            LOG_INFO("Loading engine configuration from %0", lib::CommandLine::GetOption("engineConfig"));
            config_ = std::unique_ptr<EngineConfig>(content::Content::Load<EngineConfig>(lib::CommandLine::GetOption("engineConfig")));
        }
        else {
            LOG_INFO("Loading default engine configuration");
            config_ = std::unique_ptr<EngineConfig>(content::Content::Load<EngineConfig>(DEFAULT_ENGINECONFIG_FILENAME));
        }

        if (!config_) {
            LOG_ERROR("No engine configuration loaded");
            return false;
        }

        if (lib::CommandLine::HasOption("engineLogFilename"))
            config_->SetLogFilename(lib::CommandLine::GetOption("engineLogFile"));

        log_file_ = std::unique_ptr<std::ofstream>(new std::ofstream(config_->GetLogFilename()));
        Log::Get().AddOutputStream(*log_file_);

        LOG_INFO("Initiliazing engine");

        info_.executablePath = lib::CommandLine::GetProgram();

        //script_environment_ = ScriptEnvironment::Load(*this);

        if (!config_->GetPlatformConfig()) {
            LOG_INFO("Creating default platform config");
            config_->SetPlatformConfig(new platform::DefaultPlatformConfig());
        }

        platform_ = std::unique_ptr<platform::Platform>(platform::Platform::Create(*this, *config_->GetPlatformConfig()));

        if (!platform_->Initialize()) {
            LOG_ERROR("Platform failed to initialize. Can't initialize engine.");
            return false;
        }

        LOG_INFO("Loading addins");
        for (const std::string& addin_filename:config_->GetAddinFilenames()) {
            if (!LoadAddin(addin_filename)) {
                LOG_ERROR("Failed to load addin %0", addin_filename);
                return false;
            }

        }

        return true;

        /*
        Script *engineScript = Script::Load(scriptContext, filename_);
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
            LOG_INFO("Nothing to run. Returning");
            return;
        }

        LOG_INFO("Starting game");
        if (!game_->Start()) {
            LOG_INFO("Failed to start game. Returning");
            return;
        }

        UpdateComponentsCache();

        LOG_INFO("Notify systems that a new game has been started");
        for (auto& system_pair:systems_) {
            framework::System& system = *system_pair.second;
            system.GameStarted(*game_);
        }

        while (game_->GetStatus()==framework::GameStatus::Running) {
            platform_->HandleEvents();

            framework::GameTime gameTime;

            for (auto iter = systems_.begin(); iter!=systems_.end(); ++iter)
                iter->second->Update(gameTime);

            game_->Update(gameTime);

            
            platform_->SwapBuffers();
        }

    }

    void Engine::Stop() {

        if (!game_) {
            LOG_INFO("No game is currently running.");
            return;
        }

        game_->Stop();

    }

    bool Engine::LoadGame(const std::string& filename) {

        framework::GameSpecification* game_spec = content::Content::Load<framework::GameSpecification>(filename);
        if (!game_spec) {
            LOG_ERROR("Failed to load game specification from %0", filename);
            return false;
        }

        game_ = std::unique_ptr<framework::Game>(framework::Game::Create(game_spec));
        if (!game_) {
            LOG_ERROR("Failed to create game");
            return false;
        }
        
        return LoadGame(*game_);

    }

    bool Engine::LoadGame(framework::Game& game) {

        if (game_&&game_.get()!=&game) {
            UnloadGame();
            game_.reset(&game);
        }
        else if (!game_)
            game_.reset(&game);

        LOG_INFO("Initializing game");
        if (!game_->Initialize(*this)) {
            LOG_ERROR("Failed to initialize game");
            return false;
        }

        LOG_INFO("Loading global game content");
        if (!game_->LoadGlobalContent()) {
            LOG_ERROR("Failed to load global content");
            return false;
        }

        UpdateComponentsCache();

        LOG_INFO("Notify systems that a new game has been loaded");
        for (auto& system_pair:systems_) {
            framework::System& system = *system_pair.second;
            system.GameLoaded(game);
        }

        LOG_INFO("Game %0 loaded and initialized", (const std::string&)game_->GetHeader().GetName());

        return true;
    }

    void Engine::UnloadGame() {

        if (!game_) {
            LOG_INFO("No game is currently running.");
            return;
        }

        game_->UnloadContent();

    }

    bool Engine::LoadAddin(const std::string& filename) {

        addin::Addin* addin = addin::Addin::Load(*this, filename);
        if (!addin)
            return false;

        addins_.push_back(addin);

        // If the engine_ has already been initialized, we should add the addin filename
        // to the engine_ configuration
        if (status_>EngineStatus::Created)
            config_->AddAddinFilename(filename);

        LOG_INFO("Sucessfully loaded addin %0 from %1\n", addin->GetHeader().GetName(), filename);

        return true;

    }

    bool Engine::HasSystemType(const std::string& type_name) const {

        // TODO this method should be re-implemented or removed. The original functionality has been moved 
        // System::IsTypeAvailable

        return false;

    }

    //void Engine::LoadSystem(const string &name, const string &type_name) {
    //
    //    if (components_.find(type_name) != components_.end())
    //        printf("The system with the specified name (%s) already exists\n", type_name.c_str());
    //
    //    components_[type_name] = System::Load(*this, new SystemConfig(name, type_name));
    //
    //}

    bool Engine::LoadSystem(framework::SystemConfig& system_config) {

        const std::string& name = system_config.GetName();
        const std::string& type_name = system_config.GetTypeName();

        bool name_found = systems_.find(name)!=systems_.end();
        bool type_found = systems_by_type_.find(type_name)!=systems_by_type_.end();
        if (name_found&&type_found) {
            LOG_ERROR("The system with the specified name (%0) and type (%1) already exists", name, type_name);
            return true;
        }
        else if (name_found) {
            LOG_ERROR("The system with name (%0) already exists with different type", name);
            return false;
        }
        else if (type_found) {
            LOG_ERROR("There already exists a system with the specified type (%0)", type_name);
            return false;
        }

        framework::System* system = framework::System::Create(*this, system_config);

        LOG_INFO("Initializing system %0", name);
        if (!system->Initialize()) {
            LOG_ERROR("Couldn't initialize system %0", name);
            return false;
        }

        systems_[name].reset(system);
        systems_by_type_[type_name] = system;

        return true;

    }

    std::optional<std::reference_wrapper<framework::System>> Engine::GetSystemByName(const std::string& name) {

        if (this->systems_.find(name)==this->systems_.end())
            return std::optional<std::reference_wrapper<framework::System>>();
        return *this->systems_[name];

    }

    std::optional<std::reference_wrapper<framework::System>> Engine::GetSystemByType(const std::string& type_name) {
        
        if (this->systems_by_type_.find(type_name)==this->systems_by_type_.end())
            return std::optional<std::reference_wrapper<framework::System>>();
        return *this->systems_by_type_[type_name];

    }

    std::optional<const std::vector<std::reference_wrapper<framework::Component>>> Engine::GetComponentsByName(const std::string& name) {

        if (!components_by_name_.count(name))
            return std::optional<const std::vector<std::reference_wrapper<framework::Component>>>();
        
        return components_by_name_[name];

    }

    std::optional<const std::vector<std::reference_wrapper<framework::Component>>> Engine::GetComponentsByType(const std::string& type_name) {
        
        if (!components_by_type_.count(type_name))
            return std::optional<const std::vector<std::reference_wrapper<framework::Component>>>();

        return std::optional<const std::vector<std::reference_wrapper<framework::Component>>>(components_by_type_[type_name]);
    }

    scripting::ScriptEnvironment& Engine::GetScriptEnvironment() { return *script_environment_; }
    platform::Platform& Engine::GetPlatform() { return *platform_; }
    framework::Game& Engine::GetGame() { return *game_; }

    Log& Engine::GetLog() {
        return *log_;
    }

    const EngineInfo& Engine::GetInfo() { return (const EngineInfo&)info_; }

    void Engine::UpdateComponentsCache() {
    
        if (!game_)
            return;

        for (framework::Entity& entity:game_->GetEntities()) {
            for (framework::Component& component:entity.GetComponents()) {
                
                const std::string& component_name = component.GetConfig().GetName();
                if (components_by_name_.find(component_name)==components_by_name_.end())
                    components_by_name_[component_name] = {};
                components_by_name_[component_name].push_back(component);
                
                const std::string& component_type = component.GetConfig().GetTypeName();
                if (components_by_type_.find(component_type)==components_by_type_.end())
                    components_by_type_[component_type] = {};
                components_by_type_[component_type].push_back(component);
            }
        }
    }

    void Engine::shutdown() {

        platform_->Shutdown();
        
        for (addin::Addin* addin:addins_)
            addin->Unload(*this);

        delete script_environment_;

    }

    void scriptableLoadAddin(const v8::FunctionCallbackInfo<v8::Value>& args) {

        v8::Local<v8::Object> self = args.Holder();
        v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

        Engine* engine = (Engine*)wrap->Value();
        v8::String::Utf8Value filename(args.GetIsolate(), args[0]);
        engine->LoadAddin(*filename);

    }

    void scriptableLoadGame(const v8::FunctionCallbackInfo<v8::Value>& args) {

        v8::Local<v8::Object> self = args.Holder();
        v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

        Engine* engine = (Engine*)wrap->Value();
        v8::String::Utf8Value filename(args.GetIsolate(), args[0]);
        engine->LoadGame(*filename);

    }
    void Engine::Scriptable::Register(scripting::ScriptEnvironment& environment) {

        _Scriptable::Register(environment);

        v8::Local<v8::ObjectTemplate> engine = v8::ObjectTemplate::New(environment.GetIsolate());
        engine->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "loadGame", v8::NewStringType::kNormal).ToLocalChecked(),
            v8::FunctionTemplate::New(environment.GetIsolate(), scriptableLoadGame));
        engine->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "loadAddin", v8::NewStringType::kNormal).ToLocalChecked(),
            v8::FunctionTemplate::New(environment.GetIsolate(), scriptableLoadAddin));

        //(*(*environment.GetContext())->Global)->Set(v8::String::NewFromUtf8(environment.GetIsolate(), "engine_", v8::NewStringType::kNormal).ToLocalChecked(), engine_);

    }

}
