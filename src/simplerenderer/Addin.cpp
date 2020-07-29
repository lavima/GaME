/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace game::graphics::vulkan;

#include "Addin.h"
#include "Config.h"
#include "SimpleRenderer.h"

namespace game::addin {

    SystemProvider* SystemProvider::singleton_ = nullptr;

    bool CreateAddin(Engine& engine, AddinHeader& header, AddinBindingInfo* create_info) {

        create_info->type_flags = static_cast<uint32_t>(AddinType::System);

        create_info->system_creator = &SystemProvider::Get();

        return true;

    }

    SystemProvider& SystemProvider::Get() {
        
        if (!singleton_)
            singleton_ = new SystemProvider();
        
        return *singleton_;

    }

    SystemConfig* SystemProvider::Load(data::xml::XmlNode root_node) {
        return nullptr;
    }

    System* SystemProvider::Create(Engine& engine, SystemConfig& config) {
        return nullptr;
    }

    framework::Component* SystemProvider::Create(const string& name, const string& type_name) {
        return nullptr;
    }
    framework::Component* SystemProvider::Create(framework::ComponentConfig& config) {
        return nullptr;
    }
}