/*
File: SimpleRenderer.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

SimpleRenderer::SimpleRenderer(Engine &engine) : EngineComponent(engine) {
  
    vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkAppInfo.apiVersion = VK_API_VERSION_1_0;
    
    const GameInfo *gameInfo = &engine.GetGame()->GetInfo();
    vkAppInfo.pApplicationName = gameInfo->Name.c_str();
    vkAppInfo.applicationVersion = VK_MAKE_VERSION(gameInfo->MajorVersion, gameInfo->MinorVersion, gameInfo->Release);

    const EngineInfo *engineInfo = &engine.GetInfo();
    vkAppInfo.pEngineName = engineInfo->Name.c_str();
    vkAppInfo.engineVersion = VK_MAKE_VERSION(engineInfo->MajorVersion, engineInfo->MinorVersion, engineInfo->Release);

}

void SimpleRenderer::Initialize() {

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &vkAppInfo;

}

void SimpleRenderer::Update(GameTime &gameTime) {

}
