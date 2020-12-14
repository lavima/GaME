/*
 * Filename: GLFWVulkan.h
 * Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::platform {

    class GAME_API GLFWVulkan : public Platform, public IVulkanPlatform {

    private:

        GLFWwindow* window_;

        std::vector<std::string> required_extensions_;

        GLFWVulkan(Engine& engine, PlatformConfig& config);

    public:

        ~GLFWVulkan() override;

        bool Initialize() override;

        void Shutdown() override;

        void HandleEvents() override;

        void SwapBuffers() override;

        double GetSystemTime() override;

        std::vector<std::reference_wrapper<const std::string>> GetRequiredExtensions() const override;
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

}
