#pragma once

namespace game::platform {

    /*
    * IVulkanPlatform provides an interface for Vulkan specific platform functions
    */
    class GAME_API IVulkanPlatform {
    public:

        virtual std::vector<std::reference_wrapper<const std::string>> GetRequiredExtensions() const = 0;

        virtual bool CreateSurface(VkInstance, VkSurfaceKHR*) = 0;

    };

}