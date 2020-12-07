/*
* Filename: GLFWVulkan.h
* Author: Lars Vidar Magnusson
*/

#ifdef PLATFORM_GLFWVULKAN

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>

#include <pugixml.hpp>
#include <v8.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "../global.h"
#include "../lib/file_path.h"
#include "../lib/string_util.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/content.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "../scripting/script_environment.h"
#include "../scripting/script.h"
#include "../scripting/scriptable.h"
#include "../platform/input_key.h"
#include "../platform/platform_config.h"
#include "../platform/platform.h"
#include "../framework/framework.h"
#include "../framework/system_info.h"
#include "../framework/game_time.h"
#include "../framework/system_config.h"
#include "../framework/component_config.h"
#include "../framework/component.h"
#include "../framework/entity_specification.h"
#include "../framework/entity.h"
#include "../framework/game_header.h"
#include "../framework/game_config.h"
#include "../framework/game_specification.h"
#include "../framework/game.h"
#include "../framework/system.h"
#include "../framework/component_info.h"
#include "../addin/system_provider.h"
#include "../addin/addin_header.h"
#include "../addin/addin.h"
#include "../log.h"
#include "../engine_config.h"
#include "../engine.h"
#include "platform_config.h"
#include "platform.h"
#include "vulkan_platform.h"
#include "glfw_vulkan_config.h"
#include "glfw_vulkan.h"

namespace game::platform {

    GLFWVulkan::GLFWVulkan(Engine& engine, PlatformConfig& config)
        : Platform(PLATFORM_GLFWVULKAN_NAME, engine, config) {
        window_ = nullptr;
    }

    void callbackKey(GLFWwindow* window, int, int, int, int);

    bool GLFWVulkan::Initialize() {

        GraphicalPlatformConfig& config = (GraphicalPlatformConfig&)GetConfig();

        LOG_INFO("Initializing GLFW");
        if (!glfwInit()) {
            LOG_ERROR("Could not initialize GLFW");
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        LOG_INFO("Creating GLFW window with Vulkan support");
        window_ = glfwCreateWindow(config.GetWidth(),
            config.GetHeight(),
            GetEngine().GetInfo().GetName().c_str(),
            nullptr, nullptr);
        if (!window_) {
            const char* description;
            glfwGetError(&description);
            LOG_ERROR("Could not create GLFW window: %s", description);
            return false;
        }

        uint32_t glfw_extension_count = 0;
        const char** glfw_extensions;
        glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
        required_extensions_ = std::vector<std::string>(glfw_extensions, glfw_extensions+glfw_extension_count);

        return true;

    }

    void GLFWVulkan::Shutdown() {


        if (window_!=nullptr)
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

    void* GLFWVulkan::LoadLibrary(const std::string& filename) {
        HMODULE handle = LoadLibraryA(filename.c_str());
        return (void*)handle;
    }

    void GLFWVulkan::UnloadLibrary(void* handle) {

    }

    void* GLFWVulkan::LoadLibrarySymbol(void* handle, const std::string& name) {
        void* address = GetProcAddress((HMODULE)handle, name.c_str());
        return address;
    }

    double GLFWVulkan::GetSystemTime() {
        return glfwGetTime();
    }

    std::vector<std::reference_wrapper<const std::string>> GLFWVulkan::GetRequiredExtensions() const {
        return std::vector<std::reference_wrapper<const std::string>>(required_extensions_.begin(), required_extensions_.end());
    }

    bool GLFWVulkan::CreateSurface(VkInstance instance, VkSurfaceKHR* surface) {
        VkResult result = glfwCreateWindowSurface(instance, window_, nullptr, surface);
        return result==VK_SUCCESS;
    }

    void callbackKey(GLFWwindow* window, int, int, int, int) {

        GLFWVulkan* platform = (GLFWVulkan*)glfwGetWindowUserPointer(window);

    }

    GLFWVulkan::Creator GLFWVulkan::Creator::singleton_;

    GLFWVulkan::Creator::Creator() {
        Platform::RegisterImplementation(PLATFORM_GLFWVULKAN_NAME, &singleton_);
    }

    Platform* GLFWVulkan::Creator::Create(Engine& engine, PlatformConfig& config) {
        return new GLFWVulkan(engine, config);
    }

}

#endif // PLATFORM_GLFWVULKAN
