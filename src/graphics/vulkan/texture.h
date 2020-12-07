#pragma once

namespace game::graphics::vulkan {

    class Texture {
    private:

        VkDevice device_;

        VkImage texture_image_;
        VkDeviceMemory texture_memory_;
        VkImageView texture_view_;
        VkSampler texture_sampler_;

        Texture(VkDevice device);
        
    public:
        static Texture* Create(VkPhysicalDevice physical_device, VkDevice device,
            VkCommandPool command_pool, VkQueue queue, VkSharingMode sharing_mode, 
            const std::vector<uint32_t>& queue_indices, Image& image);

        ~Texture();

        void Destroy();


    };

}