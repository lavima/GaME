/*
File: DefaultPlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::platform {

#ifdef PLATFORM_GLFWVULKAN


    class GAME_API DefaultPlatformConfig : public GraphicalPlatformConfig {
    public:

        DefaultPlatformConfig() : GraphicalPlatformConfig(PLATFORM_GLFWVULKAN_NAME, 800, 600, false) {}

    };

#endif

}