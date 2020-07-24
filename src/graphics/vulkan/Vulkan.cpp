/*
File: Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#include "../../GaME.h"

namespace game::graphics::vulkan {

    bool QueueFamilyIndices::IsComplete() {
        return graphics_index.has_value()&&present_index.has_value()&&transfer_index.has_value();
    }

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

            if (queue_family.queueFlags&VK_QUEUE_TRANSFER_BIT&&!(queue_family.queueFlags&VK_QUEUE_GRAPHICS_BIT))
                indices.transfer_index = i;

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

    bool Vulkan::FindMemoryType(VkPhysicalDevice device, uint32_t type_filter, VkMemoryPropertyFlags properties, uint32_t* memory_type) {

        VkPhysicalDeviceMemoryProperties mem_properties;
        vkGetPhysicalDeviceMemoryProperties(device, &mem_properties);

        for (uint32_t i = 0; i<mem_properties.memoryTypeCount; i++) {
            if (type_filter&(1<<i) &&
                (mem_properties.memoryTypes[i].propertyFlags&properties)==properties) {
                *memory_type = i;
                return true;
            }
        }

        return false;

    }

    const string Vulkan::GetResultString(VkResult result) {
        if (result==VK_SUCCESS)
            return string("Success");
        else if (result==VK_NOT_READY)
            return string("Not Ready");
        else if (result==VK_TIMEOUT)
            return string("Timeout");
        else if (result==VK_EVENT_SET)
            return string("Event Set");
        else if (result==VK_EVENT_RESET)
            return string("Event Reset");
        else if (result==VK_INCOMPLETE)
            return string("Incomplete");
        else if (result==VK_ERROR_OUT_OF_HOST_MEMORY)
            return string("Out of Host Memory");
        else if (result==VK_ERROR_OUT_OF_DEVICE_MEMORY)
            return string("Out of Device Memory");
        else if (result==VK_ERROR_INITIALIZATION_FAILED)
            return string("Initialization Failed");
        else if (result==VK_ERROR_DEVICE_LOST)
            return string("Device Lost");
        else if (result==VK_ERROR_MEMORY_MAP_FAILED)
            return string("Memory Map Failed");
        else if (result==VK_ERROR_LAYER_NOT_PRESENT)
            return string("Layer Not Present");
        else if (result==VK_ERROR_EXTENSION_NOT_PRESENT)
            return string("Extension Not Present");
        else if (result==VK_ERROR_FEATURE_NOT_PRESENT)
            return string("Feature Not Present");
        else if (result==VK_ERROR_INCOMPATIBLE_DRIVER)
            return string("Incompatible Driver");
        else if (result==VK_ERROR_TOO_MANY_OBJECTS)
            return string("Too Many Objects");
        else if (result==VK_ERROR_FORMAT_NOT_SUPPORTED)
            return string("Format Not Supported");
        else if (result==VK_ERROR_FRAGMENTED_POOL)
            return string("Fragmented Pool");
        else
            return string("UNKNOWN Vulkan Error");
    }

    bool Vulkan::CreateBuffer(VkPhysicalDevice physical_device, VkDevice device, 
        VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
        VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices,
        VkBuffer* buffer, VkDeviceMemory* buffer_memory) {

        VkBufferCreateInfo buffer_info{};
        buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_info.pNext = nullptr;
        buffer_info.flags = 0;
        buffer_info.size = size;
        buffer_info.usage = usage;
        buffer_info.sharingMode = sharing_mode;
        buffer_info.queueFamilyIndexCount = static_cast<uint32_t>(queue_indices.size());
        buffer_info.pQueueFamilyIndices = queue_indices.data();

        if (vkCreateBuffer(device, &buffer_info, nullptr, buffer)!=VK_SUCCESS) 
            return false;

        VkMemoryRequirements mem_requirements;
        vkGetBufferMemoryRequirements(device, *buffer, &mem_requirements);

        VkMemoryAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.pNext = nullptr;
        alloc_info.allocationSize = mem_requirements.size;
        alloc_info.memoryTypeIndex = 0;

        FindMemoryType(physical_device, mem_requirements.memoryTypeBits, properties, &alloc_info.memoryTypeIndex);

        if (vkAllocateMemory(device, &alloc_info, nullptr, buffer_memory)!=VK_SUCCESS) 
            return false;

        vkBindBufferMemory(device, *buffer, *buffer_memory, 0);

        return true;

    }

    bool Vulkan::CopyBuffer(VkDevice device, VkCommandPool command_pool, VkQueue queue, 
        VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size) {

        VkCommandBuffer command_buffer = BeginCommandBuffer(device, command_pool, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkBufferCopy copy_region{};
        copy_region.srcOffset = 0;
        copy_region.dstOffset = 0;
        copy_region.size = size;
        vkCmdCopyBuffer(command_buffer, src_buffer, dst_buffer, 1, &copy_region);

        EndCommandBuffer(device, command_pool, queue, command_buffer);

        return true;
    
    }

    bool Vulkan::CopyBufferToImage(VkDevice device, VkCommandPool command_pool, VkQueue queue,
        VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {

        VkCommandBuffer command_buffer = BeginCommandBuffer(device, command_pool, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = { width, height, 1 };

        vkCmdCopyBufferToImage(command_buffer, buffer, image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        EndCommandBuffer(device, command_pool, queue, command_buffer);

        return true;

    }

    bool Vulkan::CreateImage(VkPhysicalDevice physical_device, VkDevice device, uint32_t width, uint32_t height,
        VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
        VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices,
        VkImage* image, VkDeviceMemory* image_memory) {

        VkImageCreateInfo image_info{};
        image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_info.pNext = nullptr;
        image_info.flags = 0;
        image_info.imageType = VK_IMAGE_TYPE_2D;
        image_info.format = format;
        image_info.extent.width = width;
        image_info.extent.height = height;
        image_info.extent.depth = 1;
        image_info.mipLevels = 1;
        image_info.arrayLayers = 1;
        image_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_info.tiling = tiling;
        image_info.usage = usage;
        image_info.sharingMode = sharing_mode;
        image_info.queueFamilyIndexCount = queue_indices.size();
        image_info.pQueueFamilyIndices = queue_indices.data();
        image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(device, &image_info, nullptr, image)!=VK_SUCCESS)
            return false;

        VkMemoryRequirements mem_requirements;
        vkGetImageMemoryRequirements(device, *image, &mem_requirements);

        VkMemoryAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = mem_requirements.size;
        FindMemoryType(physical_device, mem_requirements.memoryTypeBits, properties, &alloc_info.memoryTypeIndex);

        if (vkAllocateMemory(device, &alloc_info, nullptr, image_memory)!=VK_SUCCESS)
            return false;

        vkBindImageMemory(device, *image, *image_memory, 0);

        return true;
    }

    bool Vulkan::CreateTextureImage(VkPhysicalDevice physical_device, VkDevice device, 
        VkCommandPool command_pool, VkQueue queue,
        Image& image, VkSharingMode sharing_mode, const vector<uint32_t>& queue_indices,
        VkImage* texture_image, VkDeviceMemory* texture_image_memory) {

        if (!image.GetData().size())
            return false;

        VkDeviceSize image_size = image.GetData().size();

        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;

        if (!CreateBuffer(physical_device, device, image_size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            sharing_mode, queue_indices,
            &staging_buffer, &staging_buffer_memory))
            return false;

        void* data;
        vkMapMemory(device, staging_buffer_memory, 0, image_size, 0, &data);
        memcpy(data, image.GetData().data(), static_cast<size_t>(image_size));
        vkUnmapMemory(device, staging_buffer_memory);

        if (!CreateImage(physical_device, device, image.GetWidth(), image.GetHeight(), 
            VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, 
            VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            sharing_mode, queue_indices, texture_image, texture_image_memory))
            return false;
       
        ChangeImageLayout(device, command_pool, queue, *texture_image, VK_FORMAT_R8G8B8A8_SRGB,
            VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        CopyBufferToImage(device, command_pool, queue, staging_buffer, *texture_image, image.GetWidth(), image.GetHeight());
        ChangeImageLayout(device, command_pool, queue, *texture_image, VK_FORMAT_R8G8B8A8_SRGB,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        vkDestroyBuffer(device, staging_buffer, nullptr);
        vkFreeMemory(device, staging_buffer_memory, nullptr);

        return true;

    }

    bool Vulkan::ChangeImageLayout(VkDevice device, VkCommandPool command_pool, VkQueue queue, 
        VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout) {

        VkCommandBuffer command_buffer = BeginCommandBuffer(device, command_pool, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags source_stage;
        VkPipelineStageFlags destination_stage;

        if (old_layout==VK_IMAGE_LAYOUT_UNDEFINED&&new_layout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (old_layout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL&&new_layout==VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else
            return false;

        vkCmdPipelineBarrier(
            command_buffer,
            source_stage, destination_stage,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrier
        );


        EndCommandBuffer(device, command_pool, queue, command_buffer);

        return true;

    }

    VkCommandBuffer Vulkan::BeginCommandBuffer(VkDevice device, VkCommandPool command_pool, VkCommandBufferUsageFlags flags) {

        VkCommandBufferAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.pNext = nullptr;
        alloc_info.commandPool = command_pool;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandBufferCount = 1;

        VkCommandBuffer command_buffer;
        vkAllocateCommandBuffers(device, &alloc_info, &command_buffer);

        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.pNext = nullptr;
        begin_info.flags = flags;
        begin_info.pInheritanceInfo = nullptr;

        vkBeginCommandBuffer(command_buffer, &begin_info);

        return command_buffer;

    }

    void Vulkan::EndCommandBuffer(VkDevice device, VkCommandPool command_pool, VkQueue queue, VkCommandBuffer command_buffer) {

        vkEndCommandBuffer(command_buffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &command_buffer;

        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(queue);

        vkFreeCommandBuffers(device, command_pool, 1, &command_buffer);

    }

    VkVertexInputBindingDescription Vertex::GetBindingDescription() {

        VkVertexInputBindingDescription description{};
        description.binding = 0;
        description.stride = sizeof(Vertex);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        
        return description;

    }

    array<VkVertexInputAttributeDescription, 2> Vertex::GetAttributeDescriptions() {
        
        array<VkVertexInputAttributeDescription, 2> description{};

        description[0].binding = 0;
        description[0].location = 0;
        description[0].format = VK_FORMAT_R32G32_SFLOAT;
        description[0].offset = offsetof(Vertex, position);

        description[1].binding = 0;
        description[1].location = 1;
        description[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        description[1].offset = offsetof(Vertex, color);

        return description;

    }

}