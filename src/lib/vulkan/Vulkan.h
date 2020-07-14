/*
File: Vulkan.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* QueueFamilyIndices holds optional queue family indices. This is used to check retrieve
* queue indices from the Vulkan implementation
*/
struct QueueFamilyIndices {

    optional<uint32_t> graphics_index;
    optional<uint32_t> present_index;

    bool IsComplete();
};

/*
* SwapChainDetails holds data for describing a swap chain
*/
struct SwapChainDetails {

    VkSurfaceCapabilitiesKHR capabilities;
    vector<VkSurfaceFormatKHR> formats;
    vector<VkPresentModeKHR> present_modes;

};

class Vulkan {
public:
    static bool HasGraphicsQueue(VkPhysicalDevice device);

    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

    static bool CheckDeviceExtensionSupport(VkPhysicalDevice device, const vector<reference_wrapper<const string>> required_extensions);

    static SwapChainDetails GetSwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR surface);

    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& available_formats);

    static VkPresentModeKHR ChooseSwapPresentMode(const vector<VkPresentModeKHR>& available_modes);

    static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D desired_extent);

    static const string GetResultString(VkResult);
};