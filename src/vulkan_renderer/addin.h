/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::vulkanrenderer {

    class SystemProvider : public addin::ISystemProvider, public addin::IComponentProvider {
    private:
        static SystemProvider* singleton_;
        SystemProvider() {}
    public:
        static SystemProvider& Get();

        framework::SystemConfig* Load(content::xml::XmlNode root_node) override;

        framework::System* Create(Engine& engine, framework::SystemConfig& config) override;

        framework::Component* Create(framework::Entity& entity, framework::ComponentConfig& config) override;

        framework::ComponentConfig* Create(const std::string& name, const std::string& type_name) override;
        framework::ComponentConfig* Create(content::xml::XmlNode root_node) override;

    };



    extern "C" {



        __declspec(dllexport) bool Register(Engine& engine, addin::AddinHeader& header, addin::AddinBindingInfo* create_info);


    }

}
