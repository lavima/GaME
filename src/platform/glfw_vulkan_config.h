#pragma once

namespace game::platform {

#define PLATFORM_GLFWVULKAN_NAME "GLFWVulkan"

#define XMLNAME_PLATFORMCONFIG_EXTENSION "Extension"

    class GAME_API GLFWVulkanConfig : GraphicalPlatformConfig {
    private:

    public:

        GLFWVulkanConfig();

        using GraphicalPlatformConfig::GetWidth;
        using GraphicalPlatformConfig::GetHeight;
        using GraphicalPlatformConfig::GetFullscreen;

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

    private:

        class Loader : public PlatformConfig::Loader {
        private:
            static Loader singleton_;
        public:
            Loader();
            PlatformConfig* Load(const std::string& implementation_name, content::xml::XmlNode root_node);
        };
    };

}
