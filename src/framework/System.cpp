/*
File: System.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

namespace game {

#ifndef DLL_BUILD
    unordered_map<string, System::ICreator*>* System::creators_ = nullptr;
#endif

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

        assert(creators_);

        if (!IsTypeAvailable(config.GetTypeName())) {
            engine.GetLog().AddEvent(EventType::Error, "Could not find the specified game component type %s", config.GetTypeName());
            return nullptr;
        }

        return (*creators_)[config.GetTypeName()]->Create(engine, config);

    }

    void System::RegisterType(const string& typeName, ICreator* creator) {

        if (!creators_)
            creators_ = new unordered_map<string, ICreator*>();

        creators_->insert_or_assign(typeName, creator);

    }

    bool System::IsTypeAvailable(const string& type_name) {
        
        auto iter = creators_->find(type_name);
        if (iter==creators_->end())
            return false;

        return true;

    }

}