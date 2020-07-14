/*
 * Filename: GLFWVulkan.h
 * Author: Lars Vidar Magnusson
 */

#pragma once

#define PLATFORM_GLFWVULKAN_NAME "GLFWVulkan"

class GLFWVulkan : public Platform, public IVulkanPlatform {

private:

    GLFWwindow* window_;

    vector<string> required_extensions_;

    GLFWVulkan(Engine& engine, PlatformConfig& config);

public:

    bool Initialize() override;

    void Shutdown() override;

    void HandleEvents() override;

    void SwapBuffers() override;

    void* LoadLibrary(const string& filename) override;

    void UnloadLibrary(void* handle) override;

    void* LoadLibrarySymbol(void* handle, const string& name) override;

    double GetSystemTime() override;


    const vector<reference_wrapper<const string>> GetRequiredExtensions() override;
    bool CreateSurface(VkInstance, VkSurfaceKHR*) override;

private:

    class Creator : public Platform::Creator {
    private:
        static Creator singleton_;
    public:
        Creator();
        Platform* Create(Engine& engine, PlatformConfig& config) override;
    };    

};
