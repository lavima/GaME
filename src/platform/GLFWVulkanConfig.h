#pragma once

namespace game::platform {

#define XMLNAME_PLATFORMCONFIG_EXTENSION "Extension"

    class GAME_API GLFWVulkanConfig : GraphicalPlatformConfig {
    private:

    public:

        GLFWVulkanConfig();

        using GraphicalPlatformConfig::GetWidth;
        using GraphicalPlatformConfig::GetHeight;
        using GraphicalPlatformConfig::GetFullscreen;

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

    private:

        class Loader : public PlatformConfig::Loader {
        private:
            static Loader singleton_;
        public:
            Loader();
            PlatformConfig* Load(const string& implementation_name, data::xml::XmlNode root_node);
        };
    };

}