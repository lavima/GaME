/*
File: DefaultPlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#ifdef PLATFORM_GLFWVULKAN


class DefaultPlatformConfig : public GraphicalPlatformConfig {
public:

    DefaultPlatformConfig() : GraphicalPlatformConfig(PLATFORM_GLFWVULKAN_NAME, 800, 600, false) {}

};

#endif


