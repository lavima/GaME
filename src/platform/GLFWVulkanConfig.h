#pragma once

#define XMLNAME_PLATFORMCONFIG_EXTENSION "Extension"

class GLFWVulkanConfig : GraphicalPlatformConfig {
private:

public:
    
    GLFWVulkanConfig();

    using GraphicalPlatformConfig::GetWidth;
    using GraphicalPlatformConfig::GetHeight;
    using GraphicalPlatformConfig::GetFullscreen;

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

private:
    class Loader : public PlatformConfig::Loader {
    private:
        static Loader singleton_;
    public:
        Loader();
        PlatformConfig* Load(const string& implementation_name, XmlNode root_node);
    };
};