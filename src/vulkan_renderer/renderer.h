/*
File: renderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define VULKANRENDERER_TYPENAME "VulkanRenderer"

#define VULKANRENDERER_VERTEXSHADER_FILENAME "vulkan_renderer/test.vert.spirv"
#define VULKANRENDERER_FRAGMENTSHADER_FILENAME "vulkan_renderer/test.frag.spirv"

namespace game::vulkanrenderer {

    class MeshComponent;

    class VulkanRenderer : public framework::System {
        friend class SystemProvider;
    private:
        
        platform::GLFWVulkan* platform_;

        
        VkInstance instance_;

        VkPhysicalDevice physical_device_;

        VkDevice device_;

        graphics::vulkan::QueueFamilyIndices queue_indices_;

        VkSurfaceKHR surface_;

        VkQueue graphics_queue_;
        VkQueue present_queue_;
        VkQueue transfer_queue_;

        VkSwapchainKHR swap_chain_;

        std::vector<VkImage> swap_chain_images_;
        std::vector<VkImageView> swap_chain_image_views_;

        VkFormat swap_chain_image_format_;
        VkExtent2D swap_chain_extent_;

        VkRenderPass render_pass_;

        VkDescriptorSetLayout descriptor_set_layout_;

        VkPipelineLayout pipeline_layout_;
        VkPipeline graphics_pipeline_;

        std::vector<VkFramebuffer> swap_chain_framebuffers_;

        VkCommandPool command_pool_;
        VkCommandPool transfer_command_pool_;

        std::vector<VkCommandBuffer> command_buffers_;

        std::vector<VkSemaphore> image_available_semaphores_;
        std::vector<VkSemaphore> render_finished_semaphores_;
        std::vector<VkFence> in_flight_fences_;
        std::vector<VkFence> images_in_flight_fences_;

        std::unique_ptr<graphics::vulkan::Shader> shader_;

        std::vector<VkBuffer> uniform_buffers_;
        std::vector<VkDeviceMemory> uniform_buffers_memory_;

        VkDescriptorPool descriptor_pool_;
        std::vector<VkDescriptorSet> descriptor_sets_;

        size_t current_frame_;

        std::vector<MeshComponent*> components_;

#ifdef NDEBUG
        const std::vector<const char*> validation_layers_{};
#else
        const std::vector<std::string> validation_layers_ = {
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
        bool FindSuitablePhysicalDevice(std::vector<std::reference_wrapper<const std::string>> extensions);
        bool CreateLogicalDevice(std::vector<std::reference_wrapper<const std::string>> extensions);
        bool CreateSwapChain();
        bool CreateRenderPass();
        bool CreateDescriptorSetLayout();
        bool CreateGraphicsPipeline();
        bool CreateFramebuffers();
        bool CreateCommandPools();
        bool CreateUniformBuffers();
        bool CreateDescriptorPool();
        bool CreateDescriptorSets();
        bool CreateCommandBuffers();
        bool CreateSynchronizationObjects();

        bool UpdateDescriptorSets(uint32_t image_index);
        bool UpdateUniformBuffer(uint32_t image_index);

        VulkanRenderer(Engine& engine, framework::SystemConfig& config);

    public:

        virtual bool Initialize() override;
        virtual void GameLoaded(framework::Game& game) override;
        virtual void GameStarted(framework::Game& game) override;
        virtual bool Update(framework::GameTime&) override;
        virtual void Destroy() override;

        VkPhysicalDevice GetPhysicalDevice();
        VkDevice GetDevice();
        VkQueue GetTransferQueue();
        VkCommandPool GetTransferCommandPool();
        graphics::vulkan::QueueFamilyIndices& GetQueueIndices();

        class Creator : public framework::System::ICreator {
        private:
            static Creator* singleton_;
            Creator();
        public:
            static Creator* Get();
            framework::System* Create(Engine& engine, framework::SystemConfig& config) override;
        };

    };
}
