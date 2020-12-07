/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

#include "Addin.h"

namespace game::vulkangui {

    SystemProvider* SystemProvider::singleton_ = nullptr;

    bool Register(Engine& engine, addin::AddinHeader& header, addin::AddinBindingInfo* binding_info) {

        Log::Set(engine.GetLog());

        binding_info->type_flags = addin::AddinType::System | addin::AddinType::Component;

        binding_info->system_provider = &SystemProvider::Get();
        binding_info->component_provider = &SystemProvider::Get();

        return true;

    }

    SystemProvider& SystemProvider::Get() {
        
        if (!singleton_)
            singleton_ = new SystemProvider();
        
        return *singleton_;

    }

    framework::SystemConfig* SystemProvider::Load(data::xml::XmlNode root_node) {
        
        return nullptr;

    }

    framework::System* SystemProvider::Create(Engine& engine, framework::SystemConfig& config) {
        return nullptr;
    }

    framework::Component* SystemProvider::Create(framework::Entity& entity, framework::ComponentConfig& config) {
        return nullptr;
    }
    framework::ComponentConfig* SystemProvider::Create(const string& name, const string& type_name) {
        return nullptr;
    }
    framework::ComponentConfig* SystemProvider::Create(data::xml::XmlNode root_node) {
        return nullptr;
    }
}