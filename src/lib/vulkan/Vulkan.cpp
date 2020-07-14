/*
File: Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#include "../../GaME.h"

bool Vulkan::HasGraphicsQueue(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    for (const auto& queue_family:queue_families) {

        if (queue_family.queueFlags&VK_QUEUE_GRAPHICS_BIT)
            return true;

    }

    return false;
}

QueueFamilyIndices Vulkan::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {

    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    int i = 0;
    for (const auto& queue_family:queue_families) {

        if (queue_family.queueFlags&VK_QUEUE_GRAPHICS_BIT)
            indices.graphics_index = i;

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);
        if (present_support)
            indices.present_index = i;

        if (indices.IsComplete())
            break;

        i++;
    }

    return indices;

}

bool Vulkan::CheckDeviceExtensionSupport(VkPhysicalDevice device, const vector<reference_wrapper<const string>> required_extensions) {

    uint32_t extension_count;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);
    vector<VkExtensionProperties> available_extensions(extension_count);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

    set<string> required(required_extensions.begin(), required_extensions.end());

    for (const auto& extension:available_extensions)
        required.erase(extension.extensionName);

    return required.empty();

}

SwapChainDetails Vulkan::GetSwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR surface) {

    SwapChainDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

    if (format_count!=0) {
        details.formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
    }

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

    if (present_mode_count!=0) {
        details.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
    }

    return details;

}

VkSurfaceFormatKHR Vulkan::ChooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& available_formats) {

    for (const auto& format:available_formats) {
        if (format.format==VK_FORMAT_B8G8R8A8_SRGB&&format.colorSpace==VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }

    return available_formats[0];

}

VkPresentModeKHR Vulkan::ChooseSwapPresentMode(const vector<VkPresentModeKHR>& available_modes) {

    for (const auto& mode:available_modes) {
        if (mode==VK_PRESENT_MODE_MAILBOX_KHR) {
            return mode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Vulkan::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D desired_extent) {
    if (capabilities.currentExtent.width!=UINT32_MAX)
        return capabilities.currentExtent;

    desired_extent.width = max(capabilities.minImageExtent.width, min(capabilities.maxImageExtent.width, desired_extent.width));
    desired_extent.height = max(capabilities.minImageExtent.height, min(capabilities.maxImageExtent.height, desired_extent.height));

    return desired_extent;

}
const string Vulkan::GetResultString(VkResult result) {
  if (result == VK_SUCCESS)
    return string("Success");
  else if (result == VK_NOT_READY)
    return string("Not Ready");
  else if (result == VK_TIMEOUT)
    return string("Timeout");
  else if (result == VK_EVENT_SET)
    return string("Event Set");
  else if (result == VK_EVENT_RESET)
    return string("Event Reset");
  else if (result == VK_INCOMPLETE)
    return string("Incomplete");
  else if (result == VK_ERROR_OUT_OF_HOST_MEMORY)
    return string("Out of Host Memory");
  else if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
    return string("Out of Device Memory");
  else if (result == VK_ERROR_INITIALIZATION_FAILED)
    return string("Initialization Failed");
  else if (result == VK_ERROR_DEVICE_LOST)
    return string("Device Lost");
  else if (result == VK_ERROR_MEMORY_MAP_FAILED)
    return string("Memory Map Failed");
  else if (result == VK_ERROR_LAYER_NOT_PRESENT)
    return string("Layer Not Present");
  else if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
    return string("Extension Not Present");
  else if (result == VK_ERROR_FEATURE_NOT_PRESENT)
    return string("Feature Not Present");
  else if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
    return string("Incompatible Driver");
  else if (result == VK_ERROR_TOO_MANY_OBJECTS)
    return string("Too Many Objects");
  else if (result == VK_ERROR_FORMAT_NOT_SUPPORTED)
    return string("Format Not Supported");
  else if (result == VK_ERROR_FRAGMENTED_POOL)
    return string("Fragmented Pool");
  else
    return string("UNKNOWN Vulkan Error");
}
