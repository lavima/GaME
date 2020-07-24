/*
File: System.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

namespace game {

    unordered_map<string, System::Creator*> System::system_providers_;

    System::System(Engine& engine, SystemConfig& config) {

        engine_ = &engine;
        config_ = &config;

    }

    Engine& System::GetEngine() {
        return *engine_;
    }

    SystemConfig& System::GetConfig() {
        return *config_;
    }

    System* System::Create(Engine& engine, SystemConfig& config) {

        if (!IsTypeAvailable(config.GetTypeName())) {
            engine.GetLog().AddEvent(EventType::Error, "Could not find the specified game component type %s", config.GetTypeName());
            return nullptr;
        }

        return system_providers_[config.GetTypeName()]->Create(engine, config);

    }

    void System::RegisterProvider(const string& typeName, Creator* creator) {

        system_providers_.insert_or_assign(typeName, creator);

    }

    bool System::IsTypeAvailable(const string& type_name) {
        
        auto iter = system_providers_.find(type_name);
        if (iter==system_providers_.end())
            return false;

        return true;

    }

}