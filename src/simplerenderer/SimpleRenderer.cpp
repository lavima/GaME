/*
File: SimpleRenderer.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

SimpleRenderer::SimpleRenderer(Engine &engine) : EngineComponent(engine) {
  
    vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkAppInfo.apiVersion = VK_API_VERSION_1_0;
    
    const GameInfo *gameInfo = &engine.GetGame().GetInfo();
    vkAppInfo.pApplicationName = gameInfo->GetName().c_str();
    vkAppInfo.applicationVersion = 
        VK_MAKE_VERSION(gameInfo->GetVersion().GetMajor(), gameInfo->GetVersion().GetMinor(), gameInfo->GetVersion().GetRelease());

    const EngineInfo *engineInfo = &engine.GetInfo();
    vkAppInfo.pEngineName = engineInfo->GetName().c_str();
    vkAppInfo.engineVersion = VK_MAKE_VERSION(engineInfo->GetVersion().GetMajor(), engineInfo->GetVersion().GetMinor(), engineInfo->GetVersion().GetRelease());

}

void SimpleRenderer::Initialize() {

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &vkAppInfo;

    const char *extensions[]{
        "VK_KHR_surface",
        "VK_KHR_wayland_surface"
    };

    createInfo.enabledExtensionCount = 2;
    createInfo.ppEnabledExtensionNames = extensions;

    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &vkInstance)!=VK_SUCCESS)
        throw std::runtime_error("Failed to create Vulkan instance");

}

void SimpleRenderer::Update(GameTime &gameTime) {

}
