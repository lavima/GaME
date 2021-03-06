/*
File: VulkanRenderer.cpp
Author: Lars Vidar Magnusson
*/

#include "../game.h"

using namespace game::graphics::vulkan;

#include "config.h"
#include "mesh_component.h"
#include "renderer.h"

namespace game::vulkanrenderer {

    static const framework::SystemInfo vulkan_renderer_info(VULKANRENDERER_TYPENAME, "Vulkan renderer", Version(0, 0, 1));

#ifdef _DEBUG
    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        
        std::string messageTypeString;
        if (messageType&VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
            messageTypeString = "GEN";
        else if (messageType&VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
            messageTypeString = "VAL";
        else if (messageType&VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
            messageTypeString = "PERF";

        if (messageSeverity&VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
            LOG_TRACE("VULKAN %0 %1", messageTypeString, pCallbackData->pMessage);
        else if (messageSeverity&VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
            LOG_INFO("VULKAN %0 %1", messageTypeString, pCallbackData->pMessage);
        else if (messageSeverity&VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            LOG_WARNING("VULKAN %0 %1", messageTypeString, pCallbackData->pMessage);
        else if (messageSeverity&VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            LOG_ERROR("VULKAN %0 %1", messageTypeString, pCallbackData->pMessage);

        return VK_FALSE;

    }
#endif

    bool VulkanRenderer::CreateInstance() {
        
        const EngineInfo& engine_info = GetEngine().GetInfo();
        const framework::GameHeader& game_header = GetEngine().GetGame().GetHeader();

        //platform::GraphicalPlatformConfig& config = (platform::GraphicalPlatformConfig&)GetConfig();

        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for (const std::string& layer_name:validation_layers_) {
            bool layer_found = false;

            for (const auto& layer_properties:available_layers) {
                if (layer_name==layer_properties.layerName) {
                    layer_found = true;
                    break;
                }
            }

            if (!layer_found) {
                LOG_ERROR("Couldn't find validation layer %0", layer_name.c_str());
                return false;
            }
        }

        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = game_header.GetName().c_str();
        app_info.applicationVersion = VK_MAKE_VERSION(game_header.GetVersion().GetMajor(),
            game_header.GetVersion().GetMinor(),
            game_header.GetVersion().GetRelease());
        app_info.pEngineName = engine_info.GetName().c_str();
        app_info.engineVersion = VK_MAKE_VERSION(engine_info.GetVersion().GetMajor(),
            engine_info.GetVersion().GetMinor(),
            engine_info.GetVersion().GetRelease());
        app_info.apiVersion = VK_API_VERSION_1_0;

        std::vector<std::reference_wrapper<const std::string>> platform_extensions = platform_->GetRequiredExtensions();

        std::vector<const char*> required_extensions;
        transform(platform_extensions.begin(), platform_extensions.end(), back_inserter(required_extensions),
            [&](const std::string& ext) { return ext.c_str(); });
#ifdef _DEBUG
        required_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;
        create_info.enabledExtensionCount = static_cast<uint32_t>(required_extensions.size());
        create_info.ppEnabledExtensionNames = required_extensions.data();
#ifdef NDEBUG
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
#else
        create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers_.size());
        std::vector<const char*> validation_layers_c;
        transform(validation_layers_.begin(), validation_layers_.end(), back_inserter(validation_layers_c),
            [&](const std::string& layer) { return layer.c_str(); });
        create_info.ppEnabledLayerNames = validation_layers_c.data();
#endif

        LOG_INFO("Extensions:");
        for (const std::string& extension:required_extensions)
            LOG_INFO("\t%0", extension.c_str());

        VkResult result = vkCreateInstance(&create_info, nullptr, &instance_);
        if (result!=VK_SUCCESS) 
            return false;

        return true;

    }

#ifdef _DEBUG
    bool VulkanRenderer::CreateDebugMessenger() {

        VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
        debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debug_create_info.pfnUserCallback = DebugCallback;
        debug_create_info.pUserData = nullptr; 

        if (CreateDebugUtilsMessengerEXT(instance_, &debug_create_info, nullptr, &debug_messenger_)!=VK_SUCCESS)
            return false;

        return true;
    }
#endif 

    bool VulkanRenderer::FindSuitablePhysicalDevice(std::vector<std::reference_wrapper<const std::string>> extensions) {
        
        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices(instance_, &device_count, nullptr);
        if (!device_count) {
            return false;
        }
        std::vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(instance_, &device_count, devices.data());

        for (VkPhysicalDevice device : devices) {

            VkPhysicalDeviceProperties device_properties;
            vkGetPhysicalDeviceProperties(device, &device_properties);
            if (device_properties.deviceType!=VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                continue;

            if (!Vulkan::HasGraphicsQueue(device))
                continue;

            if (!Vulkan::CheckDeviceExtensionSupport(device, extensions))
                continue;

            VkPhysicalDeviceFeatures device_features;
            vkGetPhysicalDeviceFeatures(device, &device_features);

            if (!device_features.samplerAnisotropy)
                return false;

            SwapChainDetails swap_chain_details = Vulkan::GetSwapChainDetails(device, surface_);
            if (swap_chain_details.formats.empty()||swap_chain_details.present_modes.empty())
                return false;

            physical_device_ = device;
            
            return true;

        }

        return false;

    }

    bool VulkanRenderer::CreateLogicalDevice(std::vector<std::reference_wrapper<const std::string>> extensions) {

        // Set up queues

        std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
        std::set<uint32_t> unique_queue_families =
        {   queue_indices_.graphics_index.value(), 
            queue_indices_.present_index.value(), 
            queue_indices_.transfer_index.value()  };

        float queue_priority = 1.0f;
        for (int32_t index : unique_queue_families) {
            VkDeviceQueueCreateInfo queue_create_info{};
            queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex = index;
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queue_priority;
            queue_create_infos.push_back(queue_create_info);
        }

        // Load logical device

        VkPhysicalDeviceFeatures device_features{};

        VkDeviceCreateInfo device_create_info{};
        device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_create_info.pQueueCreateInfos = queue_create_infos.data();
        device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
        device_create_info.pEnabledFeatures = &device_features;
        device_create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        std::vector<const char*> all_extensions_c;
        transform(extensions.begin(), extensions.end(), back_inserter(all_extensions_c),
            [&](const std::string& ext) { return ext.c_str(); });
        device_create_info.ppEnabledExtensionNames = all_extensions_c.data();
        device_create_info.enabledLayerCount = 0;

        LOG_INFO("Extensions:");
        for (const std::string& extension:extensions)
            LOG_INFO("\t%0", extension.c_str());

        if (vkCreateDevice(physical_device_, &device_create_info, nullptr, &device_)!=VK_SUCCESS)
            return false;

        return true;

    }

    bool VulkanRenderer::CreateSwapChain() {

        platform::GraphicalPlatformConfig& config = (platform::GraphicalPlatformConfig&)GetConfig();

        SwapChainDetails swap_chain_details = Vulkan::GetSwapChainDetails(physical_device_, surface_);

        VkSurfaceFormatKHR swap_chain_surface_format = Vulkan::ChooseSwapSurfaceFormat(swap_chain_details.formats);
        VkPresentModeKHR swap_chain_present_mode = Vulkan::ChooseSwapPresentMode(swap_chain_details.present_modes);
        VkExtent2D swap_chain_extent = Vulkan::ChooseSwapExtent(swap_chain_details.capabilities, 
            VkExtent2D{ config.GetWidth(), config.GetHeight() });

        uint32_t swap_image_count = swap_chain_details.capabilities.minImageCount+1;
        if (swap_chain_details.capabilities.maxImageCount>0&&swap_image_count>swap_chain_details.capabilities.maxImageCount) {
            swap_image_count = swap_chain_details.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR swap_chain_create_info{};
        swap_chain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swap_chain_create_info.surface = surface_;
        swap_chain_create_info.minImageCount = swap_image_count;
        swap_chain_create_info.imageFormat = swap_chain_surface_format.format;
        swap_chain_create_info.imageColorSpace = swap_chain_surface_format.colorSpace;
        swap_chain_create_info.imageExtent = swap_chain_extent;
        swap_chain_create_info.imageArrayLayers = 1;
        swap_chain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        if (queue_indices_.graphics_index.value()!=queue_indices_.present_index.value()) {
            uint32_t queueFamilyIndices[] = {
                queue_indices_.graphics_index.value(),
                queue_indices_.present_index.value() };

            swap_chain_create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swap_chain_create_info.queueFamilyIndexCount = 2;
            swap_chain_create_info.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            swap_chain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            swap_chain_create_info.queueFamilyIndexCount = 0;
            swap_chain_create_info.pQueueFamilyIndices = nullptr;
        }

        swap_chain_create_info.preTransform = swap_chain_details.capabilities.currentTransform;
        swap_chain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swap_chain_create_info.presentMode = swap_chain_present_mode;
        swap_chain_create_info.clipped = VK_TRUE;
        swap_chain_create_info.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device_, &swap_chain_create_info, nullptr, &swap_chain_)!=VK_SUCCESS) {
            return false;
        }

        // Get the swap chain images

        vkGetSwapchainImagesKHR(device_, swap_chain_, &swap_image_count, nullptr);
        swap_chain_images_.resize(swap_image_count);
        vkGetSwapchainImagesKHR(device_, swap_chain_, &swap_image_count, swap_chain_images_.data());


        // Store the swap chain surface format and extent

        swap_chain_image_format_ = swap_chain_surface_format.format;
        swap_chain_extent_ = swap_chain_extent;


        // Format image views

        swap_chain_image_views_.resize(swap_chain_images_.size());
        for (size_t index = 0; index<swap_chain_images_.size(); ++index) {
            if (!Vulkan::CreateImageView(swap_chain_images_[index], device_,
                VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB, &swap_chain_image_views_[index]))
                return false;
        }

        return true;

    }

    bool VulkanRenderer::CreateRenderPass() {

        VkAttachmentDescription color_attachment{};
        color_attachment.format = swap_chain_image_format_;
        color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment_ref{};
        color_attachment_ref.attachment = 0;
        color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &color_attachment_ref;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        render_pass_info.attachmentCount = 1;
        render_pass_info.pAttachments = &color_attachment;
        render_pass_info.subpassCount = 1;
        render_pass_info.pSubpasses = &subpass;
        render_pass_info.dependencyCount = 1;
        render_pass_info.pDependencies = &dependency;

        if (vkCreateRenderPass(device_, &render_pass_info, nullptr, &render_pass_)!=VK_SUCCESS) 
            return false;

        return true;

    }

    bool VulkanRenderer::CreateDescriptorSetLayout() {

        VkDescriptorSetLayoutBinding mvp_binding{};
        mvp_binding.binding = 0;
        mvp_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        mvp_binding.descriptorCount = 1;
        mvp_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        mvp_binding.pImmutableSamplers = nullptr;

        VkDescriptorSetLayoutBinding sampler_binding{};
        sampler_binding.binding = 1;
        sampler_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        sampler_binding.descriptorCount = 1;
        sampler_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        sampler_binding.pImmutableSamplers = nullptr;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        std::array<VkDescriptorSetLayoutBinding, 2> bindings = { mvp_binding, sampler_binding };
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        layoutInfo.pBindings = bindings.data();

        if (vkCreateDescriptorSetLayout(device_, &layoutInfo, nullptr, &descriptor_set_layout_)!=VK_SUCCESS)
            return false;

        return true;

    }

    bool VulkanRenderer::CreateGraphicsPipeline() {

        auto binding_description = Vertex::GetBindingDescription();
        auto attribute_descriptions = Vertex::GetAttributeDescriptions();

        VkPipelineVertexInputStateCreateInfo vertex_input_info{};
        vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_info.pNext = nullptr;
        vertex_input_info.flags = 0;
        vertex_input_info.vertexBindingDescriptionCount = 1;
        vertex_input_info.pVertexBindingDescriptions = &binding_description;
        vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribute_descriptions.size());
        vertex_input_info.pVertexAttributeDescriptions = attribute_descriptions.data();

        VkPipelineInputAssemblyStateCreateInfo input_assembly{};
        input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly.pNext = nullptr;
        input_assembly.flags = 0;
        input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        input_assembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swap_chain_extent_.width;
        viewport.height = (float)swap_chain_extent_.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swap_chain_extent_;

        VkPipelineViewportStateCreateInfo viewport_state{};
        viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state.viewportCount = 1;
        viewport_state.pViewports = &viewport;
        viewport_state.scissorCount = 1;
        viewport_state.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f;
        rasterizer.depthBiasClamp = 0.0f;
        rasterizer.depthBiasSlopeFactor = 0.0f;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f;
        multisampling.pSampleMask = nullptr;
        multisampling.alphaToCoverageEnable = VK_FALSE;
        multisampling.alphaToOneEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState color_blend_attachment{};
        color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT|VK_COLOR_COMPONENT_G_BIT|VK_COLOR_COMPONENT_B_BIT|VK_COLOR_COMPONENT_A_BIT;
        color_blend_attachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo color_blending{};
        color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blending.logicOpEnable = VK_FALSE;
        color_blending.logicOp = VK_LOGIC_OP_COPY;
        color_blending.attachmentCount = 1;
        color_blending.pAttachments = &color_blend_attachment;
        color_blending.blendConstants[0] = 0.0f;
        color_blending.blendConstants[1] = 0.0f;
        color_blending.blendConstants[2] = 0.0f;
        color_blending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipeline_layout_info{};
        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = 1;
        pipeline_layout_info.pSetLayouts = &descriptor_set_layout_;
        pipeline_layout_info.pushConstantRangeCount = 0;
        pipeline_layout_info.pPushConstantRanges = nullptr;

        LOG_INFO("Creating graphics pipeline layout");
        if (vkCreatePipelineLayout(device_, &pipeline_layout_info, nullptr, &pipeline_layout_)!=VK_SUCCESS) {
            LOG_ERROR("Couldn't create pipeline layout");
            return false;
        }

        std::vector<VkPipelineShaderStageCreateInfo> shader_stages = shader_->GetShaderStages();

        VkGraphicsPipelineCreateInfo pipeline_info{};
        pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipeline_info.stageCount = shader_stages.size();
        pipeline_info.pStages = shader_stages.data();
        pipeline_info.pVertexInputState = &vertex_input_info;
        pipeline_info.pInputAssemblyState = &input_assembly;
        pipeline_info.pViewportState = &viewport_state;
        pipeline_info.pRasterizationState = &rasterizer;
        pipeline_info.pMultisampleState = &multisampling;
        pipeline_info.pDepthStencilState = nullptr;
        pipeline_info.pColorBlendState = &color_blending;
        pipeline_info.pDynamicState = nullptr;
        pipeline_info.layout = pipeline_layout_;
        pipeline_info.renderPass = render_pass_;
        pipeline_info.subpass = 0;
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
        pipeline_info.basePipelineIndex = -1;

        if (vkCreateGraphicsPipelines(device_, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &graphics_pipeline_)!=VK_SUCCESS)
            return false;

        return true;

    }

    bool VulkanRenderer::CreateFramebuffers() {

        swap_chain_framebuffers_.resize(swap_chain_image_views_.size());

        for (size_t i = 0; i<swap_chain_image_views_.size(); i++) {

            VkImageView attachments[] = {
                swap_chain_image_views_[i]
            };

            VkFramebufferCreateInfo framebuffer_info{};
            framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebuffer_info.renderPass = render_pass_;
            framebuffer_info.attachmentCount = 1;
            framebuffer_info.pAttachments = attachments;
            framebuffer_info.width = swap_chain_extent_.width;
            framebuffer_info.height = swap_chain_extent_.height;
            framebuffer_info.layers = 1;

            if (vkCreateFramebuffer(device_, &framebuffer_info, nullptr, &swap_chain_framebuffers_[i])!=VK_SUCCESS) 
                return false;

        }

        return true;

    }

    bool VulkanRenderer::CreateCommandPools() {

        VkCommandPoolCreateInfo pool_info{};
        pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.pNext = nullptr;
        pool_info.queueFamilyIndex = queue_indices_.graphics_index.value();
        pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(device_, &pool_info, nullptr, &command_pool_)!=VK_SUCCESS)
            return false;

        VkCommandPoolCreateInfo transfer_pool_info{};
        transfer_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        transfer_pool_info.pNext = nullptr;
        transfer_pool_info.queueFamilyIndex = queue_indices_.transfer_index.value();
        transfer_pool_info.flags = 0;

        if (vkCreateCommandPool(device_, &transfer_pool_info, nullptr, &transfer_command_pool_)!=VK_SUCCESS)
            return false;

        return true;
    }

    bool VulkanRenderer::CreateUniformBuffers() {

        VkDeviceSize buffer_size = sizeof(graphics::ModelViewProjection);

        uniform_buffers_.resize(swap_chain_images_.size());
        uniform_buffers_memory_.resize(swap_chain_images_.size());

        std::vector<uint32_t> queue_family_indices = { queue_indices_.graphics_index.value() };

        for (size_t i = 0; i<swap_chain_images_.size(); ++i) {
            
            if (!Vulkan::CreateBuffer(physical_device_, device_, buffer_size,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                VK_SHARING_MODE_EXCLUSIVE, queue_family_indices,
                &uniform_buffers_[i], &uniform_buffers_memory_[i]))
                return false;

        }

        return true;

    }

    bool VulkanRenderer::CreateDescriptorPool() {

        std::array<VkDescriptorPoolSize, 2> pool_sizes{};
        pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        pool_sizes[0].descriptorCount = static_cast<uint32_t>(swap_chain_images_.size());
        pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        pool_sizes[1].descriptorCount = static_cast<uint32_t>(swap_chain_images_.size());

        VkDescriptorPoolCreateInfo pool_info{};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.poolSizeCount = static_cast<uint32_t>(pool_sizes.size());
        pool_info.pPoolSizes = pool_sizes.data();
        pool_info.maxSets = static_cast<uint32_t>(swap_chain_images_.size());

        if (vkCreateDescriptorPool(device_, &pool_info, nullptr, &descriptor_pool_)!=VK_SUCCESS)
            return false;

        return true;

    }

    bool VulkanRenderer::CreateDescriptorSets() {
        
        std::vector<VkDescriptorSetLayout> layouts(swap_chain_images_.size(), descriptor_set_layout_);

        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = descriptor_pool_;
        alloc_info.descriptorSetCount = static_cast<uint32_t>(swap_chain_images_.size());
        alloc_info.pSetLayouts = layouts.data();

        descriptor_sets_.resize(swap_chain_images_.size());
        if (vkAllocateDescriptorSets(device_, &alloc_info, descriptor_sets_.data())!=VK_SUCCESS)
            return false;

        for (size_t i = 0; i<swap_chain_images_.size(); ++i) {
            
            VkDescriptorBufferInfo buffer_info{};
            buffer_info.buffer = uniform_buffers_[i];
            buffer_info.offset = 0;
            buffer_info.range = sizeof(graphics::ModelViewProjection);

            VkDescriptorImageInfo image_info{};
            image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            //image_info.imageView =
            
            VkWriteDescriptorSet descriptor_write{};
            descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptor_write.dstSet = descriptor_sets_[i];
            descriptor_write.dstBinding = 0;
            descriptor_write.dstArrayElement = 0;
            descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptor_write.descriptorCount = 1;
            descriptor_write.pBufferInfo = &buffer_info;
            descriptor_write.pImageInfo = nullptr;
            descriptor_write.pTexelBufferView = nullptr; 

            vkUpdateDescriptorSets(device_, 1, &descriptor_write, 0, nullptr);

        }

        return true;

    }

    bool VulkanRenderer::CreateCommandBuffers() {

        command_buffers_.resize(swap_chain_framebuffers_.size());

        VkCommandBufferAllocateInfo command_alloc_info{};
        command_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        command_alloc_info.commandPool = command_pool_;
        command_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        command_alloc_info.commandBufferCount = (uint32_t)command_buffers_.size();

        LOG_INFO("Allocate command buffers");
        if (vkAllocateCommandBuffers(device_, &command_alloc_info, command_buffers_.data())!=VK_SUCCESS) {
            LOG_ERROR("Couldn't create command buffer");
            return false;
        }

        //for (size_t i = 0; i<command_buffers_.size(); i++) {
        //    VkCommandBufferBeginInfo begin_info{};
        //    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        //    begin_info.flags = 0;
        //    begin_info.pInheritanceInfo = nullptr;

        //    LOG_INFO("Begin command buffer for framebuffer[%d]", i);
        //    if (vkBeginCommandBuffer(command_buffers_[i], &begin_info)!=VK_SUCCESS) {
        //        LOG_ERROR("Failed to begin command buffer");
        //        return false;
        //    }

        //    VkRenderPassBeginInfo render_pass_info{};
        //    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        //    render_pass_info.renderPass = render_pass_;
        //    render_pass_info.framebuffer = swap_chain_framebuffers_[i];
        //    render_pass_info.renderArea.offset = { 0, 0 };
        //    render_pass_info.renderArea.extent = swap_chain_extent_;
        //    VkClearValue clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
        //    render_pass_info.clearValueCount = 1;
        //    render_pass_info.pClearValues = &clear_color;

        //    vkCmdBeginRenderPass(command_buffers_[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        //    vkCmdBindPipeline(command_buffers_[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics_pipeline_);

        //    //VkBuffer vertex_buffers[] = { vertex_buffer_ };
        //    //VkDeviceSize offsets[] = { 0 };
        //    //vkCmdBindVertexBuffers(command_buffers_[i], 0, 1, vertex_buffers, offsets);
        //    //vkCmdBindIndexBuffer(command_buffers_[i], index_buffer_, 0, VK_INDEX_TYPE_UINT16);

        //    vkCmdBindDescriptorSets(command_buffers_[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout_, 0, 1, &descriptor_sets_[i], 0, nullptr);
        //    //vkCmdDrawIndexed(command_buffers_[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

        //    vkCmdEndRenderPass(command_buffers_[i]);

        //    LOG_INFO("End command buffer", i);
        //    if (vkEndCommandBuffer(command_buffers_[i])!=VK_SUCCESS) {
        //        LOG_ERROR("Failed to end command buffer");
        //        return false;
        //    }

        //}

        return true;

    }

    bool VulkanRenderer::CreateSynchronizationObjects() {

        image_available_semaphores_.resize(DEFAULT_FRAMES_IN_FLIGHT);
        render_finished_semaphores_.resize(DEFAULT_FRAMES_IN_FLIGHT);
        in_flight_fences_.resize(DEFAULT_FRAMES_IN_FLIGHT);

        images_in_flight_fences_.resize(swap_chain_images_.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphore_info{};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fence_info{};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i<DEFAULT_FRAMES_IN_FLIGHT; ++i) {
            if (vkCreateSemaphore(device_, &semaphore_info, nullptr, &image_available_semaphores_[i])!=VK_SUCCESS||
                vkCreateSemaphore(device_, &semaphore_info, nullptr, &render_finished_semaphores_[i])!=VK_SUCCESS||
                vkCreateFence(device_, &fence_info, nullptr, &in_flight_fences_[i])!=VK_SUCCESS) {
                LOG_ERROR("Failed to create semaphores for frame %", i);
                return false;
            }
        }

        return true;

    }

    bool VulkanRenderer::UpdateDescriptorSets(uint32_t image_index) {
        
        VkDescriptorBufferInfo buffer_info{};
        buffer_info.buffer = uniform_buffers_[image_index];
        buffer_info.offset = 0;
        buffer_info.range = sizeof(graphics::ModelViewProjection);

        VkDescriptorImageInfo image_info{};
        image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        //image_info.imageView = 

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_write.dstSet = descriptor_sets_[image_index];
        descriptor_write.dstBinding = 0;
        descriptor_write.dstArrayElement = 0;
        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pBufferInfo = &buffer_info;
        descriptor_write.pImageInfo = nullptr;
        descriptor_write.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(device_, 1, &descriptor_write, 0, nullptr);
        return true;
    }

    bool VulkanRenderer::UpdateUniformBuffer(uint32_t image_index) {

        graphics::ModelViewProjection mvp;
        mvp.model = glm::mat4(1.0f);
        mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        mvp.projection = glm::perspective(glm::radians(45.0f), swap_chain_extent_.width/(float)swap_chain_extent_.height, 0.1f, 10.0f);

        void* data;

        if (vkMapMemory(device_, uniform_buffers_memory_[image_index], 0, sizeof(mvp), 0, &data)!=VK_SUCCESS)
            return false;
        memcpy(data, &mvp, sizeof(mvp));
        vkUnmapMemory(device_, uniform_buffers_memory_[image_index]);

        return true;

    }

    VulkanRenderer::VulkanRenderer(Engine& engine, framework::SystemConfig& config) 
        : System(engine, vulkan_renderer_info, config) {

        platform_ = (platform::GLFWVulkan*)&engine.GetPlatform();

        instance_ = VK_NULL_HANDLE;
        physical_device_ = VK_NULL_HANDLE;

    }

    VulkanRenderer::~VulkanRenderer() {}

    bool VulkanRenderer::Initialize() {

        LOG_INFO("Creating Vulkan Instance");
        if (!CreateInstance()) {
            LOG_ERROR("Couldn't create Vulkan instance");
            return false;
        }

        LOG_INFO("Creating Vulkan Surface");
        if (!platform_->CreateSurface(instance_, &surface_)) {
            LOG_ERROR("Couldn't create window surface");
            return false;
        }

#ifdef _DEBUG
        LOG_INFO("Creating debug messenger");
        if (!CreateDebugMessenger()) {
            LOG_ERROR("Couldn't create debug messenger");
            return false;
        }
#endif
        // Load a vector with all required device extensions

        const std::vector<std::string> mandatory_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        std::set<std::string> extension_set(mandatory_extensions.begin(), mandatory_extensions.end());
        //copy(config.GetExtensions().begin(), config.GetExtensions().end(), inserter(extension_set, extension_set.begin()));
        std::vector<std::reference_wrapper<const std::string>> all_extensions(extension_set.begin(), extension_set.end());

        LOG_INFO("Checking for GPUs with Vulkan support");
        if (!FindSuitablePhysicalDevice(all_extensions)) {
            LOG_ERROR("Couldn't find suitable GPU");
            return false;
        }

        LOG_INFO("Find queue family indices");
        queue_indices_ = Vulkan::FindQueueFamilies(physical_device_, surface_);
        if (!queue_indices_.IsComplete()) {
            LOG_ERROR("Couldn't find device queues");
            return false;
        }

        LOG_INFO("Creating logical Vulkan device");
        if (!CreateLogicalDevice(all_extensions)) {
            LOG_ERROR("Couldn't create logical Vulkan device");
            return false;
        }

        // Get the queues

        vkGetDeviceQueue(device_, queue_indices_.graphics_index.value(), 0, &graphics_queue_);
        vkGetDeviceQueue(device_, queue_indices_.present_index.value(), 0, &present_queue_);
        vkGetDeviceQueue(device_, queue_indices_.transfer_index.value(), 0, &transfer_queue_);

        LOG_INFO("Creating Vulkan swap chain");
        if (!CreateSwapChain()) {
            LOG_ERROR("Couldn't create swap chain");
            return false;
        }

        LOG_INFO("Creating Vulkan render pass");
        if (!CreateRenderPass()) {
            LOG_ERROR("Couldn't create render pass");
            return false;
        }

        LOG_INFO("Loading shaders %0 and %1", VULKANRENDERER_VERTEXSHADER_FILENAME, VULKANRENDERER_FRAGMENTSHADER_FILENAME);
        shader_ = std::unique_ptr<Shader>(Shader::Create(device_,
            VULKANRENDERER_VERTEXSHADER_FILENAME, VULKANRENDERER_FRAGMENTSHADER_FILENAME));
        if (!shader_) {
            LOG_ERROR("Couldn't create the shader object");
            return false;
        }

        LOG_INFO("Creating descriptor set layout");
        if (!CreateDescriptorSetLayout()) {
            LOG_ERROR("Couldn't create descriptor set layout");
            return false;
        }

        LOG_INFO("Creating graphics pipeline");
        if (!CreateGraphicsPipeline()) {
            LOG_ERROR("Couldn't create pipeline");
            return false;
        }

        LOG_INFO("Creating framebuffers");
        if (!CreateFramebuffers()) {
            LOG_ERROR("Couldn't create framebuffers");
            return false;
        }
                

        LOG_INFO("Creating command pool");
        if (!CreateCommandPools()) {
            LOG_ERROR("Couldn't create command pool");
            return false;
        }

        LOG_INFO("Creating descriptor pool");
        if (!CreateDescriptorPool()) {
            LOG_ERROR("Couldn't create descriptor pool");
            return false;
        }

        LOG_INFO("Creating uniform buffers");
        if (!CreateUniformBuffers()) {
            LOG_ERROR("Couldn't create uniform buffers");
            return false;
        }

        LOG_INFO("Creating descriptor sets");
        if (!CreateDescriptorSets()) {
            LOG_ERROR("Couldn't create descriptor sets");
            return false;
        }

        LOG_INFO("Creating command buffers");
        if (!CreateCommandBuffers()) {
            LOG_ERROR("Couldn't create command buffers");
            return false;
        }

        LOG_INFO("Creating synchronization objects");
        if (!CreateSynchronizationObjects()) {
            LOG_ERROR("Couldn't create synchronization objects");
            return false;
        }

        current_frame_ = 0;

        return true;

    }

    void VulkanRenderer::GameLoaded(framework::Game& game) {}

    void VulkanRenderer::GameStarted(framework::Game& game) {
        components_.clear();
        auto components = *game.GetComponentsByType(MESHCOMPONENT_TYPENAME);
        components_.reserve(components.size());
        for (framework::Component& component:components) {
            MeshComponent* mesh_component = static_cast<MeshComponent*>(&component);
            components_.push_back(mesh_component);
        }
    }

    bool VulkanRenderer::Update(framework::GameTime& gameTime) {

        uint32_t image_index;
        vkAcquireNextImageKHR(device_, swap_chain_, UINT64_MAX, image_available_semaphores_[current_frame_], VK_NULL_HANDLE, &image_index);

        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        begin_info.pInheritanceInfo = nullptr;

        //LOG_INFO("Begin command buffer for framebuffer[%d]", image_index);
        if (vkBeginCommandBuffer(command_buffers_[image_index], &begin_info)!=VK_SUCCESS) {
            //LOG_ERROR("Failed to begin command buffer");
            return false;
        }

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = render_pass_;
        render_pass_info.framebuffer = swap_chain_framebuffers_[image_index];
        render_pass_info.renderArea.offset = { 0, 0 };
        render_pass_info.renderArea.extent = swap_chain_extent_;
        VkClearValue clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
        render_pass_info.clearValueCount = 1;
        render_pass_info.pClearValues = &clear_color;

        vkCmdBeginRenderPass(command_buffers_[image_index], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(command_buffers_[image_index], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics_pipeline_);

        for (MeshComponent* component:components_) {
            VkBuffer vertex_buffers[] = { component->GetVertexBuffer() };
            VkDeviceSize offsets[] = { 0 };
            vkCmdBindVertexBuffers(command_buffers_[image_index], 0, 1, vertex_buffers, offsets);
            vkCmdBindIndexBuffer(command_buffers_[image_index], component->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);

            vkCmdBindDescriptorSets(command_buffers_[image_index], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout_, 0, 1, &descriptor_sets_[image_index], 0, nullptr);
            vkCmdDrawIndexed(command_buffers_[image_index], static_cast<uint32_t>(component->GetNumIndices()), 1, 0, 0, 0);
        }
        vkCmdEndRenderPass(command_buffers_[image_index]);

        //LOG_INFO("End command buffer", image_index);
        if (vkEndCommandBuffer(command_buffers_[image_index])!=VK_SUCCESS) {
            LOG_ERROR("Failed to end command buffer");
            return false;
        }

        vkWaitForFences(device_, 1, &in_flight_fences_[current_frame_], VK_TRUE, UINT64_MAX);


        if (images_in_flight_fences_[image_index]!=VK_NULL_HANDLE) {
            vkWaitForFences(device_, 1, &images_in_flight_fences_[image_index], VK_TRUE, UINT64_MAX);
        }
        images_in_flight_fences_[image_index] = in_flight_fences_[current_frame_];

        UpdateUniformBuffer(image_index);

        VkSubmitInfo sugmit_info{};
        sugmit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore wait_semaphores[] = { image_available_semaphores_[current_frame_] };
        VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        sugmit_info.waitSemaphoreCount = 1;
        sugmit_info.pWaitSemaphores = wait_semaphores;
        sugmit_info.pWaitDstStageMask = wait_stages;
        sugmit_info.commandBufferCount = 1;
        sugmit_info.pCommandBuffers = &command_buffers_[image_index];
        VkSemaphore signal_semaphores[] = { render_finished_semaphores_[current_frame_] };
        sugmit_info.signalSemaphoreCount = 1;
        sugmit_info.pSignalSemaphores = signal_semaphores;

        vkResetFences(device_, 1, &in_flight_fences_[current_frame_]);

        if (vkQueueSubmit(graphics_queue_, 1, &sugmit_info, in_flight_fences_[current_frame_])!=VK_SUCCESS) {
            LOG_ERROR("Failed to submit draw command buffer");
            return false;
        }

        VkPresentInfoKHR present_info{};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = signal_semaphores;
        VkSwapchainKHR swap_chains[] = { swap_chain_ };
        present_info.swapchainCount = 1;
        present_info.pSwapchains = swap_chains;
        present_info.pImageIndices = &image_index;
        present_info.pResults = nullptr; // Optional

        vkQueuePresentKHR(present_queue_, &present_info);

        current_frame_ = (current_frame_+1)%DEFAULT_FRAMES_IN_FLIGHT;

        return true;

    }

    void VulkanRenderer::Destroy() {

        vkDeviceWaitIdle(device_);

        for (size_t i = 0; i<DEFAULT_FRAMES_IN_FLIGHT; ++i) {
            if (image_available_semaphores_[i]!=VK_NULL_HANDLE)
                vkDestroySemaphore(device_, image_available_semaphores_[i], nullptr);

            if (render_finished_semaphores_[i]!=VK_NULL_HANDLE)
                vkDestroySemaphore(device_, render_finished_semaphores_[i], nullptr);

            if (in_flight_fences_[i]!=VK_NULL_HANDLE)
                vkDestroyFence(device_, in_flight_fences_[i], nullptr);
        }

        if (descriptor_pool_!=VK_NULL_HANDLE)
            vkDestroyDescriptorPool(device_, descriptor_pool_, nullptr);

        for (size_t i = 0; i<swap_chain_images_.size(); i++) {
            if (uniform_buffers_[i]!=VK_NULL_HANDLE) {
                vkDestroyBuffer(device_, uniform_buffers_[i], nullptr);
                vkFreeMemory(device_, uniform_buffers_memory_[i], nullptr);
            }
        }

        if (command_pool_!=VK_NULL_HANDLE)
            vkDestroyCommandPool(device_, command_pool_, nullptr);

        for (VkFramebuffer framebuffer:swap_chain_framebuffers_) {
            if (framebuffer!=VK_NULL_HANDLE)
                vkDestroyFramebuffer(device_, framebuffer, nullptr);
        }

        if (graphics_pipeline_!=VK_NULL_HANDLE)
            vkDestroyPipeline(device_, graphics_pipeline_, nullptr);

        if (pipeline_layout_!=VK_NULL_HANDLE)
            vkDestroyPipelineLayout(device_, pipeline_layout_, nullptr);

        if (descriptor_set_layout_!=VK_NULL_HANDLE)
            vkDestroyDescriptorSetLayout(device_, descriptor_set_layout_, nullptr);

        if (render_pass_!=VK_NULL_HANDLE)
            vkDestroyRenderPass(device_, render_pass_, nullptr);

        for (VkImageView image_view:swap_chain_image_views_) {
            if (image_view!=VK_NULL_HANDLE)
                vkDestroyImageView(device_, image_view, nullptr);
        }

        if (swap_chain_!=VK_NULL_HANDLE)
            vkDestroySwapchainKHR(device_, swap_chain_, nullptr);

        if (surface_!=VK_NULL_HANDLE)
            vkDestroySurfaceKHR(instance_, surface_, nullptr);

        if (device_!=VK_NULL_HANDLE)
            vkDestroyDevice(device_, nullptr);

#ifdef _DEBUG
        if (debug_messenger_!=VK_NULL_HANDLE)
            DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
#endif

        if (instance_!=VK_NULL_HANDLE)
            vkDestroyInstance(instance_, nullptr);

    }

    VkPhysicalDevice VulkanRenderer::GetPhysicalDevice() {
        return physical_device_;
    }

    VkDevice VulkanRenderer::GetDevice() {
        return device_;
    }

    VkQueue VulkanRenderer::GetTransferQueue() {
        return transfer_queue_;
    }

    VkCommandPool VulkanRenderer::GetTransferCommandPool() {
        return transfer_command_pool_;
    }

    QueueFamilyIndices& VulkanRenderer::GetQueueIndices() {
        return queue_indices_;
    }

    VulkanRenderer::Creator* VulkanRenderer::Creator::singleton_ = nullptr;

    VulkanRenderer::Creator::Creator() {
        System::RegisterType(VULKANRENDERER_TYPENAME, this);
    }

    VulkanRenderer::Creator* VulkanRenderer::Creator::Get() {
        if (!singleton_)
            singleton_ = new Creator();
        return singleton_;
    }

    framework::System* VulkanRenderer::Creator::Create(Engine& engine, framework::SystemConfig& config) {
        return new VulkanRenderer(engine, config);
    }

}

