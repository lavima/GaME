#pragma once

/*
* IVulkanPlatform provides an interface for Vulkan specific platform functions
*/
class IVulkanPlatform {
public:

    virtual const vector<reference_wrapper<const string>> GetRequiredExtensions() = 0;

    virtual bool CreateSurface(VkInstance, VkSurfaceKHR*) = 0;

};