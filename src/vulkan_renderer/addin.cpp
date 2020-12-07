/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "../game.h"

using namespace game::graphics::vulkan;

#include "addin.h"
#include "config.h"
#include "mesh_component.h"
#include "renderer.h"

namespace game::vulkanrenderer {

    SystemProvider* SystemProvider::singleton_ = nullptr;

    bool Register(Engine& engine, addin::AddinHeader& header, addin::AddinBindingInfo* create_info) {

        Log::Set(engine.GetLog());

        create_info->type_flags = addin::AddinType::System | addin::AddinType::Component;

        create_info->system_provider = &SystemProvider::Get();
        create_info->component_provider = &SystemProvider::Get();

        return true;

    }

    SystemProvider& SystemProvider::Get() {
        
        if (!singleton_)
            singleton_ = new SystemProvider();
        
        return *singleton_;

    }

    framework::SystemConfig* SystemProvider::Load(content::xml::XmlNode root_node) {
        
        Config* config = new Config();
        
        if (!config->Load(root_node))
            return nullptr;
        
        return config;

    }

    framework::System* SystemProvider::Create(Engine& engine, framework::SystemConfig& config) {
        return new VulkanRenderer(engine, config);
    }

    framework::Component* SystemProvider::Create(framework::Entity& entity, framework::ComponentConfig& config) {
        return new MeshComponent(entity, config);
    }
    framework::ComponentConfig* SystemProvider::Create(const std::string& name, const std::string& type_name) {
        return new MeshComponentConfig(name, type_name);
    }
    framework::ComponentConfig* SystemProvider::Create(content::xml::XmlNode root_node) {
        return new MeshComponentConfig(root_node);
    }
}
