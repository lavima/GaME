#pragma once

class GLFWVulkanConfig : GraphicalPlatformConfig {
public:
    GLFWVulkanConfig();
private:
    class Loader : public PlatformConfig::Loader {
    private:
        static Loader singleton_;
    public:
        Loader();
        PlatformConfig* Load(const string& implementation_name, XmlNode root_node);
    };
};