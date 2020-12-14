#pragma once

namespace game::vulkanrenderer {

#define MESHCOMPONENT_TYPENAME "MeshComponent"

    class VulkanRenderer;

    class MeshComponent : public framework::Component {
        friend class SystemProvider;
    private:

        VulkanRenderer* renderer_;

        const std::vector<graphics::Vertex> vertices = {
            graphics::Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            graphics::Vertex{glm::vec3{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            graphics::Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            graphics::Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
        };

        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };

        VkBuffer vertex_buffer_;
        VkDeviceMemory vertex_buffer_memory_;
        VkBuffer index_buffer_;
        VkDeviceMemory index_buffer_memory_;

        std::unique_ptr<graphics::Image> image_;
        std::unique_ptr<graphics::vulkan::Texture> texture_;

        MeshComponent(framework::Entity& entity, const std::string& name, const std::string& type_name);
        MeshComponent(framework::Entity& entity, framework::ComponentConfig& config);

    public:

        ~MeshComponent() override;

        bool Initialize() override;
        void Update(const framework::GameTime& gameTime) override;
        void Destroy() override;

        VkBuffer GetVertexBuffer();
        VkBuffer GetIndexBuffer();
        uint32_t GetNumIndices();

    private:

        bool CreateVertexBuffers();
        bool CreateIndexBuffers();

    };

}
