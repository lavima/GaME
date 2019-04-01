/*
* Filename: GLFWVulkan.h
* Author: Lars Vidar Magnusson
*/

#ifdef PLATFORM_GLFW_VULKAN

#include "../GaME.h"

GLFWVulkan::GLFWVulkan(Engine &engine, PlatformConfig *config) : __GraphicalPlatformInternal(engine) {

    this->config = (GraphicalPlatformConfig *)&config;

}

Platform * GLFWVulkan::Create(Engine &engine, PlatformConfig *config) {

    return new GLFWVulkan(engine, config);

}

void callbackKey(GLFWwindow *window, int, int, int, int);

bool GLFWVulkan::Initialize() {

    Log &log = GetEngine().GetLog();

    // Initialize GLFW
    if (!glfwInit()) {
        log.AddEvent(EVENT_ERROR, "Could not initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(config->GetWidth(), config->GetHeight(), GetEngine().GetInfo().GetName().c_str(), nullptr, nullptr);
    if (!window) {
        log.AddEvent(EVENT_ERROR, "Could not initialize GLFW");
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(window, this);

    //glfwSetKeyCallback(window, 

}

void GLFWVulkan::Shutdown() {


}

void GLFWVulkan::HandleEvents() {

}

void GLFWVulkan::SwapBuffers() {

}

void *GLFWVulkan::LoadLibrary(const string &filename) {

}

void GLFWVulkan::UnloadLibrary(void *handle) {

}

void *GLFWVulkan::LoadLibrarySymbol(void *handle, const string &name) {

}

unsigned long long GLFWVulkan::GetSystemTime() {

}

void callbackKey(GLFWwindow *window, int, int, int, int) {
       
    GLFWVulkan *platform = (GLFWVulkan*)glfwGetWindowUserPointer(window);

}

#endif // PLATFORM_GLFW_VULKAN
