#pragma once

namespace game::vulkanrenderer {

    const int DEFAULT_FRAMES_IN_FLIGHT = 2;

#define XMLNAME_CONFIG_FRAMES_IN_FLIGHT "FramesInFlight"

    class Config : public framework::SystemConfig {
    private:

        uint32_t frames_in_flight_;

    public:
        
        Config();

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;


    };

    class MeshComponentConfig : public framework::ComponentConfig {
        friend class SystemProvider;
    private:
        MeshComponentConfig(const std::string& name, const std::string& type_name) : framework::ComponentConfig(name, type_name) {}
        MeshComponentConfig(content::xml::XmlNode root_node) : framework::ComponentConfig(root_node) {}
    };

}
