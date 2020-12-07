#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include "../../global.h"
#include "../../content/content.h"
#include "../image.h"
#include "../vertex.h"
#include "vulkan.h"
#include "texture.h"

namespace game::graphics::vulkan {

    Texture::Texture(VkDevice device) : device_(device) {}

    Texture::~Texture() { Destroy(); }

    void Texture::Destroy() {
        vkDestroySampler(device_, texture_sampler_, nullptr);
        vkDestroyImageView(device_, texture_view_, nullptr);
        vkDestroyImage(device_, texture_image_, nullptr);
        vkFreeMemory(device_, texture_memory_, nullptr);
    }
    
    Texture* Texture::Create(VkPhysicalDevice physical_device, VkDevice device,
        VkCommandPool command_pool, VkQueue queue, VkSharingMode sharing_mode,
        const std::vector<uint32_t>& queue_indices, Image& image) {

        Texture* texture = new Texture(device);

        if (!Vulkan::CreateTextureImage(physical_device, device, command_pool,
            queue, sharing_mode, queue_indices,
            image, &texture->texture_image_, &texture->texture_memory_))
            return nullptr;

        if (!Vulkan::CreateImageView(texture->texture_image_, device,
            VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB, &texture->texture_view_))
            return nullptr;

        if (!Vulkan::CreateTextureSampler(device, VK_FILTER_LINEAR, VK_FILTER_LINEAR,
            VK_SAMPLER_MIPMAP_MODE_LINEAR, 0.0f, 0.0f, 0.0f,
            VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT,
            VK_TRUE, 16.0f, &texture->texture_sampler_))
            return nullptr;

        return texture;
    }
    
}
