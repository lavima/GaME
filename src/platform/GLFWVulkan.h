/*
 * Filename: GLFWVulkan.h
 * Author: Lars Vidar Magnusson
 */

#pragma once

#define GLFWVULKAN_NAME "GLFWVulkan"
#define GLFWVULKAN_PLATFORM_CONFIG "glfw_vulkan.platform_config"


class GLFWVulkan : public Platform {

private:

    GraphicalPlatformConfig *config;

    GLFWwindow *window;

    GLFWVulkan(Engine &engine, PlatformConfig *config);

public:

    static Platform * Create(Engine &engine, PlatformConfig *config);

    bool Initialize();

    void Shutdown();

    void HandleEvents();

    void SwapBuffers();

    void *LoadLibrary(const string &filename);

    void UnloadLibrary(void *handle);

    void *LoadLibrarySymbol(void *handle, const string &name);

    unsigned long long GetSystemTime();

    const string &GetCommandLine();

private:

    class __Register {
        private:
            static __Register singleton;
        public:
            __Register() { Platform::RegisterImplementation(GLFWVULKAN_NAME, &(GLFWVulkan::Create)); }
    };

};
