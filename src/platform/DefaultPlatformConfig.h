/*
File: DefaultPlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#ifdef PLATFORM_GLFW_VULKAN

class DefaultPlatformConfig : public GraphicalPlatformConfig {
public:

    DefaultPlatformConfig() : GraphicalPlatformConfig(string("GLFWVulkan"), 800, 600, false) {}

};

#endif


