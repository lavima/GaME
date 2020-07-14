/*
* Filename: GLFWVulkan.h
* Author: Lars Vidar Magnusson
*/

#ifdef PLATFORM_GLFWVULKAN

#include "../GaME.h"

GLFWVulkan::GLFWVulkan(Engine& engine, PlatformConfig& config) 
    : Platform(PLATFORM_GLFWVULKAN_NAME, engine, config) {
    
    window_ = nullptr;

}

void callbackKey(GLFWwindow *window, int, int, int, int);

bool GLFWVulkan::Initialize() {

    Log &log = GetEngine().GetLog();
    GraphicalPlatformConfig& config = (GraphicalPlatformConfig&)GetConfig();

    log.AddEvent("Initializing GLFW");
    if (!glfwInit()) {
        log.AddEvent(EventType::Error, "Could not initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    log.AddEvent("Creating GLFW window with Vulkan support");
    window_ = glfwCreateWindow(config.GetWidth(),
                               config.GetHeight(), 
                               GetEngine().GetInfo().GetName().c_str(), 
                               nullptr, nullptr);
    if (!window_) {
        const char* description;
        glfwGetError(&description);
        log.AddEvent(EventType::Error, "Could not create GLFW window: %s", description);
        return false;
    }

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    required_extensions_ = vector<string>(glfw_extensions, glfw_extensions+glfw_extension_count);

    return true;

}

void GLFWVulkan::Shutdown() {

    
    if (window_ != nullptr)
        glfwDestroyWindow(window_);

    glfwTerminate();

}

void GLFWVulkan::HandleEvents() {
    
    if (glfwWindowShouldClose(window_))
        GetEngine().Stop();

    glfwPollEvents();

}

void GLFWVulkan::SwapBuffers() {

    glfwSwapBuffers(window_);

}

void *GLFWVulkan::LoadLibrary(const string &filename) {
    HMODULE handle = LoadLibraryA(filename.c_str());
    return (void*)handle;
}

void GLFWVulkan::UnloadLibrary(void *handle) {

}

void *GLFWVulkan::LoadLibrarySymbol(void *handle, const string &name) {
    void *address = GetProcAddress((HMODULE)handle, name.c_str());
    return address;
}

double GLFWVulkan::GetSystemTime() {
    return glfwGetTime();
}

const vector<reference_wrapper<const string>> GLFWVulkan::GetRequiredExtensions() {
    return vector<reference_wrapper<const string>>(required_extensions_.begin(), required_extensions_.end());
}

bool GLFWVulkan::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {
    VkResult result = glfwCreateWindowSurface(instance, window_, nullptr, surface);
    return result==VK_SUCCESS;
}

void callbackKey(GLFWwindow *window, int, int, int, int) {
       
    GLFWVulkan *platform = (GLFWVulkan*)glfwGetWindowUserPointer(window);

}

GLFWVulkan::Creator GLFWVulkan::Creator::singleton_;

GLFWVulkan::Creator::Creator() {
    Platform::RegisterImplementation(PLATFORM_GLFWVULKAN_NAME, &singleton_);
}

Platform* GLFWVulkan::Creator::Create(Engine& engine, PlatformConfig& config) {
    return new GLFWVulkan(engine, config);
}

#endif // PLATFORM_GLFWVULKAN
