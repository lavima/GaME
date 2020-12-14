#include "../game.h"

#include "renderer.h"
#include "mesh_component.h"

namespace game::vulkanrenderer {

    MeshComponent::MeshComponent(framework::Entity& entity, const std::string& name, const std::string& type_name) 
        : Component(entity, name, type_name) {}

    MeshComponent::MeshComponent(framework::Entity& entity, framework::ComponentConfig& config)
        : Component(entity, config) {}

    MeshComponent::~MeshComponent() {}

    bool MeshComponent::Initialize() {

        auto system_optional = GetEntity().GetGame().GetSystemByType(VULKANRENDERER_TYPENAME);
        if (!system_optional)
            return false;

        renderer_ = static_cast<VulkanRenderer*>(&(*system_optional).get());

        if (!CreateVertexBuffers()) 
            return false;

        if (!CreateIndexBuffers())
            return false;

        graphics::vulkan::QueueFamilyIndices& queue_indices = renderer_->GetQueueIndices();
        std::vector<uint32_t> queue_family_indices = {
             queue_indices.graphics_index.value(),
             queue_indices.transfer_index.value() };

        image_ = std::unique_ptr<graphics::Image>(content::Content::Load<graphics::Image>("texture.jpg"));

        texture_ = std::unique_ptr<graphics::vulkan::Texture>(graphics::vulkan::Texture::Create(
            renderer_->GetPhysicalDevice(), renderer_->GetDevice(), 
            renderer_->GetTransferCommandPool(), renderer_->GetTransferQueue(),
            VK_SHARING_MODE_CONCURRENT, queue_family_indices, *image_));

        return Component::Initialize();

    }

    void MeshComponent::Update(const framework::GameTime& gameTime) {}

    void MeshComponent::Destroy() {

        if (index_buffer_!=VK_NULL_HANDLE) {
            vkDestroyBuffer(renderer_->GetDevice(), index_buffer_, nullptr);
            vkFreeMemory(renderer_->GetDevice(), index_buffer_memory_, nullptr);
        }

        if (vertex_buffer_!=VK_NULL_HANDLE) {
            vkDestroyBuffer(renderer_->GetDevice(), vertex_buffer_, nullptr);
            vkFreeMemory(renderer_->GetDevice(), vertex_buffer_memory_, nullptr);
        }

        Component::Destroy();

    }

    VkBuffer MeshComponent::GetVertexBuffer() {
        return vertex_buffer_;
    }

    VkBuffer MeshComponent::GetIndexBuffer() {
        return index_buffer_;
    }

    uint32_t MeshComponent::GetNumIndices() {
        return indices.size();
    }

    bool MeshComponent::CreateVertexBuffers() {
        
        graphics::vulkan::QueueFamilyIndices& queue_indices = renderer_->GetQueueIndices();
        
        VkDeviceSize size = sizeof(vertices[0])*vertices.size();

        std::vector<uint32_t> queue_family_indices = {
             queue_indices.graphics_index.value(),
             queue_indices.transfer_index.value() };

        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        graphics::vulkan::Vulkan::CreateBuffer(renderer_->GetPhysicalDevice(), renderer_->GetDevice(), size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            VK_SHARING_MODE_CONCURRENT, queue_family_indices,
            &staging_buffer, &staging_buffer_memory);

        void* data;
        vkMapMemory(renderer_->GetDevice(), staging_buffer_memory, 0, size, 0, &data);
        memcpy(data, vertices.data(), (size_t)size);
        vkUnmapMemory(renderer_->GetDevice(), staging_buffer_memory);

        graphics::vulkan::Vulkan::CreateBuffer(renderer_->GetPhysicalDevice(), renderer_->GetDevice(), size,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            VK_SHARING_MODE_CONCURRENT, queue_family_indices,
            &vertex_buffer_, &vertex_buffer_memory_);

        graphics::vulkan::Vulkan::CopyBuffer(renderer_->GetDevice(), 
            renderer_->GetTransferCommandPool(), renderer_->GetTransferQueue(), staging_buffer, vertex_buffer_, size);

        vkDestroyBuffer(renderer_->GetDevice(), staging_buffer, nullptr);
        vkFreeMemory(renderer_->GetDevice(), staging_buffer_memory, nullptr);

        return true;

    }

    bool MeshComponent::CreateIndexBuffers() {

        graphics::vulkan::QueueFamilyIndices& queue_indices = renderer_->GetQueueIndices();

        VkDeviceSize size = sizeof(indices[0])*indices.size();

        std::vector<uint32_t> queue_family_indices = {
             queue_indices.graphics_index.value(),
             queue_indices.transfer_index.value() };

        VkBuffer staging_buffer;
        VkDeviceMemory staging_buffer_memory;
        graphics::vulkan::Vulkan::CreateBuffer(renderer_->GetPhysicalDevice(), renderer_->GetDevice(), size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            VK_SHARING_MODE_CONCURRENT, queue_family_indices,
            &staging_buffer, &staging_buffer_memory);

        void* data;
        vkMapMemory(renderer_->GetDevice(), staging_buffer_memory, 0, size, 0, &data);
        memcpy(data, indices.data(), (size_t)size);
        vkUnmapMemory(renderer_->GetDevice(), staging_buffer_memory);

        graphics::vulkan::Vulkan::CreateBuffer(renderer_->GetPhysicalDevice(), renderer_->GetDevice(), size,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            VK_SHARING_MODE_CONCURRENT, queue_family_indices,
            &index_buffer_, &index_buffer_memory_);

        graphics::vulkan::Vulkan::CopyBuffer(renderer_->GetDevice(), 
            renderer_->GetTransferCommandPool(), renderer_->GetTransferQueue(), staging_buffer, index_buffer_, size);

        vkDestroyBuffer(renderer_->GetDevice(), staging_buffer, nullptr);
        vkFreeMemory(renderer_->GetDevice(), staging_buffer_memory, nullptr);

        return true;

    }



}
