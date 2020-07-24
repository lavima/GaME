#include "../GaME.h"

namespace game::platform {

    bool GLFWVulkanConfig::Load(data::xml::XmlNode root_node) {

        if (!GraphicalPlatformConfig::Load(root_node))
            return false;

        //for (XmlNode extension_node : root_node.GetChildren(XMLNAME_PLATFORMCONFIG_EXTENSION)) 
        //    extensions_.push_back(extension_node.GetValue());

        return true;
    }

    bool GLFWVulkanConfig::Save(data::xml::XmlNode root_node) {

        if (!GraphicalPlatformConfig::Save(root_node))
            return false;

        //for (const string& extension:extensions_) {
        //    XmlNode extension_node = root_node.AddChild(XMLNAME_PLATFORMCONFIG_EXTENSION);
        //    extension_node.SetValue(extension);
        //}

        return true;
    }


    GLFWVulkanConfig::Loader GLFWVulkanConfig::Loader::singleton_;


    GLFWVulkanConfig::Loader::Loader() {
        PlatformConfig::RegisterImplementation(PLATFORM_GLFWVULKAN_NAME, this);
    }

    PlatformConfig* GLFWVulkanConfig::Loader::Load(const string& implementation_name, data::xml::XmlNode root_node) {
        PlatformConfig* config = new GLFWVulkanConfig();
        if (!config->Load(root_node))
            return nullptr;
        return config;
    }

    GLFWVulkanConfig::GLFWVulkanConfig() : GraphicalPlatformConfig(PLATFORM_GLFWVULKAN_NAME) {}

}