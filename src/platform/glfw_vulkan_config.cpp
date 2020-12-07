#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "platform_config.h"
#include "glfw_vulkan_config.h"

namespace game::platform {

    bool GLFWVulkanConfig::Load(content::xml::XmlNode root_node) {

        if (!GraphicalPlatformConfig::Load(root_node))
            return false;

        //for (XmlNode extension_node : root_node.GetChildren(XMLNAME_PLATFORMCONFIG_EXTENSION)) 
        //    extensions_.push_back(extension_node.GetValue());

        return true;
    }

    bool GLFWVulkanConfig::Save(content::xml::XmlNode root_node) {

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

    PlatformConfig* GLFWVulkanConfig::Loader::Load(const std::string& implementation_name, content::xml::XmlNode root_node) {
        PlatformConfig* config = new GLFWVulkanConfig();
        if (!config->Load(root_node))
            return nullptr;
        return config;
    }

    GLFWVulkanConfig::GLFWVulkanConfig() : GraphicalPlatformConfig(PLATFORM_GLFWVULKAN_NAME) {}

}
