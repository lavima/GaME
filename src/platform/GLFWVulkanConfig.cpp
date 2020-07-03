#include "../GaME.h"

GLFWVulkanConfig::Loader GLFWVulkanConfig::Loader::singleton_;


GLFWVulkanConfig::Loader::Loader() {
    PlatformConfig::RegisterImplementation(PLATFORM_GLFWVULKAN_NAME, this);
}

PlatformConfig* GLFWVulkanConfig::Loader::Load(const string& implementation_name, XmlNode root_node) {
    return new GLFWVulkanConfig();
}

GLFWVulkanConfig::GLFWVulkanConfig() : GraphicalPlatformConfig(PLATFORM_GLFWVULKAN_NAME) {}
