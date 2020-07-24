/*
File: Vulkan.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::graphics::vulkan {



    /*
    * QueueFamilyIndices holds optional queue family indices. This is used to check retrieve
    * queue indices from the Vulkan implementation
    */
    struct GAME_API QueueFamilyIndices {

        optional<uint32_t> graphics_index;
        optional<uint32_t> present_index;
        optional<uint32_t> transfer_index;

        bool IsComplete();
    };

    /*
    * SwapChainDetails holds data for describing a swap chain
    */
    struct GAME_API SwapChainDetails {

        VkSurfaceCapabilitiesKHR capabilities;
        vector<VkSurfaceFormatKHR> formats;
        vector<VkPresentModeKHR> present_modes;

    };

    class GAME_API Vulkan {
    public:

        static bool HasGraphicsQueue(VkPhysicalDevice device);

        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

        static bool CheckDeviceExtensionSupport(VkPhysicalDevice device, const vector<reference_wrapper<const string>> required_extensions);

        static SwapChainDetails GetSwapChainDetails(VkPhysicalDevice device, VkSurfaceKHR surface);

        static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& available_formats);

        static VkPresentModeKHR ChooseSwapPresentMode(const vector<VkPresentModeKHR>& available_modes);

        static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VkExtent2D desired_extent);

        static bool FindMemoryType(VkPhysicalDevice device, uint32_t type_filter, VkMemoryPropertyFlags properties, uint32_t* memory_type);

        static const string GetResultString(VkResult);

        static bool CreateBuffer(VkPhysicalDevice physical_device, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, 
            VkMemoryPropertyFlags properties, VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices, 
            VkBuffer* buffer, VkDeviceMemory* buffer_memory);

        static bool CopyBuffer(VkDevice device, VkCommandPool command_pool, VkQueue queue, 
            VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);

        static bool CopyBufferToImage(VkDevice device, VkCommandPool command_pool, VkQueue queue,
            VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        static bool CreateImage(VkPhysicalDevice physical_device, VkDevice device, uint32_t width, uint32_t height,
            VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
            VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices,
            VkImage* image, VkDeviceMemory* imageMemory);

        static bool CreateTextureImage(VkPhysicalDevice physical_device, VkDevice device, 
            VkCommandPool command_pool, VkQueue queue,
            Image& image, VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices,
            VkImage* texture_image, VkDeviceMemory* texture_image_memory);

        static bool ChangeImageLayout(VkDevice device, VkCommandPool command_pool, VkQueue queue, 
            VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout layout);

        static VkCommandBuffer BeginCommandBuffer(VkDevice device, VkCommandPool command_pool, VkCommandBufferUsageFlags flags);

        static void EndCommandBuffer(VkDevice device, VkCommandPool command_pool, VkQueue queue, VkCommandBuffer command_buffer);
        
    };

    struct Vertex : public game::graphics::Vertex {

        static VkVertexInputBindingDescription GetBindingDescription();

        static array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();

    };

}