/*
File: SimpleRenderer.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

#include "SimpleRenderer.h"

SimpleRenderer::SimpleRenderer(Engine &engine, EngineComponentConfig& config) : EngineComponent(engine, config) {

    instance_ = VK_NULL_HANDLE;
    physical_device_ = VK_NULL_HANDLE;

}

bool SimpleRenderer::Initialize() {

    Log& log = GetEngine().GetLog();
    const EngineInfo& engine_info = GetEngine().GetInfo();
    const GameHeader& game_header = GetEngine().GetGame().GetHeader();
    
    GLFWVulkan& platform = (GLFWVulkan&)GetEngine().GetPlatform();
    GraphicalPlatformConfig& config = (GraphicalPlatformConfig&)GetConfig();

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

    vector<reference_wrapper<const string>> required_extensions = platform.GetRequiredExtensions();

    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = required_extensions.size();
    vector<const char*> required_extensions_c;
    transform(required_extensions.begin(), required_extensions.end(), back_inserter(required_extensions_c),
        [&](const string& ext) { return ext.c_str(); });
    create_info.ppEnabledExtensionNames = required_extensions_c.data();
    create_info.enabledLayerCount = 0;
    create_info.pNext = nullptr;

    log.AddEvent("Creating Vulkan Instance");
    log.AddEvent("Extensions:");
    for (const string& extension:required_extensions)
        log.AddEvent("\t%s", extension.c_str());
    VkResult result = vkCreateInstance(&create_info, nullptr, &instance_);
    if (result!=VK_SUCCESS) {
        log.AddEvent(EventType::Error, "Couldn't create Vulkan instance");
        return false;
    }

    log.AddEvent("Creating Vulkan Surface");
    if (!platform.CreateSurface(instance_, &surface_)) {
        log.AddEvent(EventType::Error, "Couldn't create window surface");
        return false;
    }


    // Create a vector with all required device extensions

    const vector<string> mandatory_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    set<string> extension_set(mandatory_extensions.begin(), mandatory_extensions.end());
    //copy(config.GetExtensions().begin(), config.GetExtensions().end(), inserter(extension_set, extension_set.begin()));
    vector<reference_wrapper<const string>> all_extensions(extension_set.begin(), extension_set.end());


    // Find a suitable physical device

    log.AddEvent("Checking for GPUs with Vulkan support");
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance_, &device_count, nullptr);
    if (!device_count) {
        log.AddEvent(EventType::Error, "Couldn't find GPU with Vulkan support");
        return false;
    }
    vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance_, &device_count, devices.data());

    for (VkPhysicalDevice device : devices) {

        VkPhysicalDeviceProperties device_properties;
        vkGetPhysicalDeviceProperties(device, &device_properties);
        if (device_properties.deviceType!=VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            continue;

        if (!Vulkan::HasGraphicsQueue(device))
            continue;

        if (!Vulkan::CheckDeviceExtensionSupport(device, all_extensions))
            continue;

        SwapChainDetails swap_chain_details = Vulkan::GetSwapChainDetails(device, surface_);

        if (!swap_chain_details.formats.empty()&&!swap_chain_details.present_modes.empty()) {
            physical_device_ = device;
            break;
        }

    }

    if (physical_device_==VK_NULL_HANDLE) {
        GetEngine().GetLog().AddEvent(EventType::Error, "Couldn't find suitable GPU");
        return false;
    }


    // Set up queues

    QueueFamilyIndices queue_indices = Vulkan::FindQueueFamilies(physical_device_, surface_);

    vector<VkDeviceQueueCreateInfo> queue_create_infos;
    set<uint32_t> uniqueQueueFamilies =
    { queue_indices.graphics_index.value(), queue_indices.present_index.value() };

    float queue_priority = 1.0f;
    for (int32_t index : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queue_create_info{};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = index;
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(queue_create_info);
    }


    // Create logical device

    VkPhysicalDeviceFeatures device_features{};

    VkDeviceCreateInfo device_create_info{};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.pQueueCreateInfos = queue_create_infos.data();
    device_create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
    device_create_info.pEnabledFeatures = &device_features;
    device_create_info.enabledExtensionCount = static_cast<uint32_t>(all_extensions.size());
    vector<const char*> all_extensions_c;
    transform(all_extensions.begin(), all_extensions.end(), back_inserter(all_extensions_c),
        [&](const string& ext) { return ext.c_str(); });
    device_create_info.ppEnabledExtensionNames = all_extensions_c.data();
    device_create_info.enabledLayerCount = 0;

    log.AddEvent("Creating logical Vulkan device");
    log.AddEvent("Extensions:");
    for (const string& extension:all_extensions)
        log.AddEvent("\t%s", extension.c_str());
    if (vkCreateDevice(physical_device_, &device_create_info, nullptr, &device_)!=VK_SUCCESS) {
        GetEngine().GetLog().AddEvent(EventType::Error, "Couldn't create logical Vulkan device");
        return false;
    }


    // Get the queues

    vkGetDeviceQueue(device_, queue_indices.graphics_index.value(), 0, &graphics_queue_);
    vkGetDeviceQueue(device_, queue_indices.present_index.value(), 0, &present_queue_);


    // Create swap chain

    SwapChainDetails swap_chain_details = Vulkan::GetSwapChainDetails(physical_device_, surface_);

    VkSurfaceFormatKHR swap_chain_surface_format = Vulkan::ChooseSwapSurfaceFormat(swap_chain_details.formats);
    VkPresentModeKHR swap_chain_present_mode = Vulkan::ChooseSwapPresentMode(swap_chain_details.present_modes);
    VkExtent2D swap_chain_extent = Vulkan::ChooseSwapExtent(swap_chain_details.capabilities, VkExtent2D{ config.GetWidth(), config.GetHeight() });

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

    uint32_t queueFamilyIndices[] = { queue_indices.graphics_index.value(), queue_indices.present_index.value() };

    if (queue_indices.graphics_index!=queue_indices.present_index) {
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

    log.AddEvent("Create Vulkan swap chain");
    if (vkCreateSwapchainKHR(device_, &swap_chain_create_info, nullptr, &swap_chain_)!=VK_SUCCESS) {
        GetEngine().GetLog().AddEvent(EventType::Error, "Couldn't create swap chain");
        return false;
    }


    // Get the swap chain images

    vkGetSwapchainImagesKHR(device_, swap_chain_, &swap_image_count, nullptr);
    swap_chain_images_.resize(swap_image_count);
    vkGetSwapchainImagesKHR(device_, swap_chain_, &swap_image_count, swap_chain_images_.data());


    // Store the swap chain surface format and extent

    swap_chain_image_format_ = swap_chain_surface_format.format;
    swap_chain_extent_ = swap_chain_extent;


    // Create image views

    swap_chain_image_views_.resize(swap_chain_images_.size());
    for (size_t image_index = 0; image_index<swap_chain_images_.size(); ++image_index) {

        VkImageViewCreateInfo image_view_create_info{};
        image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.image = swap_chain_images_[image_index];
        image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_create_info.format = swap_chain_image_format_;
        image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_create_info.subresourceRange.baseMipLevel = 0;
        image_view_create_info.subresourceRange.levelCount = 1;
        image_view_create_info.subresourceRange.baseArrayLayer = 0;
        image_view_create_info.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device_, &image_view_create_info, nullptr, swap_chain_image_views_.data())!=VK_SUCCESS) {
            GetEngine().GetLog().AddEvent(EventType::Error, "Couldn't create image view for swap chain images");
            return false;
        }

    }

    return true;

}

void SimpleRenderer::Update(GameTime &gameTime) {

}

void SimpleRenderer::Destroy() {

    for (auto image_view:swap_chain_image_views_) {
        if (image_view!=VK_NULL_HANDLE)
            vkDestroyImageView(device_, image_view, nullptr);
    }

    if (swap_chain_!=VK_NULL_HANDLE)
        vkDestroySwapchainKHR(device_, swap_chain_, nullptr);
    if (surface_!=VK_NULL_HANDLE)
        vkDestroySurfaceKHR(instance_, surface_, nullptr);
    if (device_!=VK_NULL_HANDLE)
        vkDestroyDevice(device_, nullptr);
    if (instance_!=VK_NULL_HANDLE)
        vkDestroyInstance(instance_, nullptr);

}
