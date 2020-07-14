/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define TYPENAME_SIMPLERENDERER "SimpleRenderer"

class SimpleRenderer : public EngineComponent {

private:

    VkInstance instance_;
    VkPhysicalDevice physical_device_;
    VkDevice device_;
    VkSurfaceKHR surface_;
    VkQueue graphics_queue_;
    VkQueue present_queue_;
    VkSwapchainKHR swap_chain_;
    vector<VkImage> swap_chain_images_;
    vector<VkImageView> swap_chain_image_views_;
    VkFormat swap_chain_image_format_;
    VkExtent2D swap_chain_extent_;

public:

  SimpleRenderer(Engine& engine, EngineComponentConfig& config);

  virtual bool Initialize() override;
  virtual void Update(GameTime &) override;
  virtual void Destroy() override;

};