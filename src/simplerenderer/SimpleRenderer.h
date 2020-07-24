/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define SIMPLERENDERER_TYPENAME "SimpleRenderer"

#define SIMPLERENDERER_VERTEXSHADER_FILENAME "SimpleRenderer/test.vert.spirv"
#define SIMPLERENDERER_FRAGMENTSHADER_FILENAME "SimpleRenderer/test.frag.spirv"

namespace game::simplerenderer {

    class SimpleRenderer : public System {
    private:
        
        const vector<Vertex> vertices = {
            Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            Vertex{glm::vec3{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
        };

        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };

        Log* log_;
        GLFWVulkan* platform_;

        
        VkInstance instance_;

        VkPhysicalDevice physical_device_;

        VkDevice device_;

        VkSurfaceKHR surface_;

        VkQueue graphics_queue_;
        VkQueue present_queue_;
        VkQueue transfer_queue_;

        VkSwapchainKHR swap_chain_;

        vector<VkImage> swap_chain_images_;
        vector<VkImageView> swap_chain_image_views_;

        VkFormat swap_chain_image_format_;
        VkExtent2D swap_chain_extent_;

        VkRenderPass render_pass_;

        VkDescriptorSetLayout descriptor_set_layout_;

        VkPipelineLayout pipeline_layout_;
        VkPipeline graphics_pipeline_;

        vector<VkFramebuffer> swap_chain_framebuffers_;

        VkCommandPool command_pool_;
        VkCommandPool transfer_command_pool_;

        vector<VkCommandBuffer> command_buffers_;

        vector<VkSemaphore> image_available_semaphores_;
        vector<VkSemaphore> render_finished_semaphores_;
        vector<VkFence> in_flight_fences_;
        vector<VkFence> images_in_flight_fences_;

        unique_ptr<Shader> shader_;

        VkBuffer vertex_buffer_;
        VkDeviceMemory vertex_buffer_memory_;
        VkBuffer index_buffer_;
        VkDeviceMemory index_buffer_memory_;

        vector<VkBuffer> uniform_buffers_;
        vector<VkDeviceMemory> uniform_buffers_memory_;

        VkDescriptorPool descriptor_pool_;
        vector<VkDescriptorSet> descriptor_sets_;

        size_t current_frame_;

#ifdef NDEBUG
        const std::vector<const char*> validation_layers_{};
#else
        const std::vector<string> validation_layers_ = {
            "VK_LAYER_KHRONOS_validation"
        };

        VkDebugUtilsMessengerEXT debug_messenger_;

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
#endif

        bool CreateInstance();
        bool CreateDebugMessenger();
        bool FindSuitablePhysicalDevice(vector<reference_wrapper<const string>> extensions);
        bool CreateLogicalDevice(vector<reference_wrapper<const string>> extensions, QueueFamilyIndices queue_indices);
        bool CreateSwapChain(QueueFamilyIndices queue_indices);
        bool CreateRenderPass();
        bool CreateDescriptorSetLayout();
        bool CreateGraphicsPipeline();
        bool CreateFramebuffers();
        bool CreateCommandPools(QueueFamilyIndices queue_indices);
        bool CreateVertexBuffers(QueueFamilyIndices queue_indices);
        bool CreateIndexBuffers(QueueFamilyIndices queue_indices);
        bool CreateUniformBuffers(QueueFamilyIndices queue_indices);
        bool CreateDescriptorPool();
        bool CreateDescriptorSets();
        bool CreateCommandBuffers();
        bool CreateSynchronizationObjects();

        bool UpdateUniformBuffer(uint32_t image_index);

        SimpleRenderer(Engine& engine, SystemConfig& config);

    public:


        virtual bool Initialize() override;
        virtual bool Update(GameTime&) override;
        virtual void Destroy() override;

        class Creator : public System::Creator {
        private:
            static Creator* singleton_;
            Creator();
        public:
            static Creator* Get();
            System* Create(Engine& engine, SystemConfig& config) override;
        };

    };
}