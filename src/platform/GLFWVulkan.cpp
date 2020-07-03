/*
* Filename: GLFWVulkan.h
* Author: Lars Vidar Magnusson
*/

#ifdef PLATFORM_GLFW_VULKAN

#include "../GaME.h"

GLFWVulkan::GLFWVulkan(Engine &engine, PlatformConfig *config) : Platform(PLATFORM_GLFWVULKAN_NAME, engine) {

    this->config_ = (GraphicalPlatformConfig *)&config;

}

void callbackKey(GLFWwindow *window, int, int, int, int);

bool GLFWVulkan::Initialize() {

    Log &log = GetEngine().GetLog();

    // Initialize GLFW
    if (!glfwInit()) {
        log.AddEvent(EventType::Error, "Could not initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(config_->GetWidth(), config_->GetHeight(), GetEngine().GetInfo().GetName().c_str(), nullptr, nullptr);
    if (!window_) {
        log.AddEvent(EventType::Error, "Could not create GLFW window");
        glfwTerminate();
        return false;
    }

    //glfwSetWindowUserPointer(window_, this);

    //glfwSetKeyCallback(window_, 

    return true;

}

void GLFWVulkan::Shutdown() {

    glfwDestroyWindow(window_);
    glfwTerminate();

}

void GLFWVulkan::HandleEvents() {

}

void GLFWVulkan::SwapBuffers() {

}

void *GLFWVulkan::LoadLibrary(const string &filename) {
    return nullptr;
}

void GLFWVulkan::UnloadLibrary(void *handle) {

}

void *GLFWVulkan::LoadLibrarySymbol(void *handle, const string &name) {
    return nullptr;
}

double GLFWVulkan::GetSystemTime() {
    return glfwGetTime();
}

void callbackKey(GLFWwindow *window, int, int, int, int) {
       
    GLFWVulkan *platform = (GLFWVulkan*)glfwGetWindowUserPointer(window);

}

#endif // PLATFORM_GLFW_VULKAN

GLFWVulkan::Creator GLFWVulkan::Creator::singleton_;

GLFWVulkan::Creator::Creator() {
    Platform::RegisterImplementation(PLATFORM_GLFWVULKAN_NAME, &singleton_);
}

Platform* GLFWVulkan::Creator::Create(Engine& engine, PlatformConfig* config) {
    return new GLFWVulkan(engine, config);
}
