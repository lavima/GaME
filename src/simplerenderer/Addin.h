/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::addin {

    class SystemProvider : public ISystemProvider {
    private:
        static SystemProvider* singleton_;
        SystemProvider() {}
    public:
        static SystemProvider& Get();

        SystemConfig* Load(data::xml::XmlNode root_node) override;

        System* Create(Engine& engine, SystemConfig& config) override;

        framework::Component* Create(const string& name, const string& type_name) override;
        framework::Component* Create(framework::ComponentConfig& config) override;

    };



    extern "C" {



        __declspec(dllexport) bool CreateAddin(Engine& engine, AddinHeader& header, AddinBindingInfo* create_info);


    }

}
