/*
 * Filename: GLFWVulkan.h
 * Author: Lars Vidar Magnusson
 */

#pragma once

#define PLATFORM_GLFWVULKAN_NAME "GLFWVulkan"

class GLFWVulkan : public Platform {

private:

    GraphicalPlatformConfig* config_;

    GLFWwindow* window_;

    GLFWVulkan(Engine& engine, PlatformConfig* config);

public:

    bool Initialize();

    void Shutdown();

    void HandleEvents();

    void SwapBuffers();

    void* LoadLibrary(const string& filename);

    void UnloadLibrary(void* handle);

    void* LoadLibrarySymbol(void* handle, const string& name);

    double GetSystemTime();

private:

    class Creator : public Platform::Creator {
    private:
        static Creator singleton_;
    public:
        Creator();
        Platform* Create(Engine& engine, PlatformConfig* config) override;
    };

    

};
