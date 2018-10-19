/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

class SimpleRenderer : public EngineComponent {

private:

    VkInstance vkInstance;
    VkApplicationInfo vkAppInfo;

public:

  SimpleRenderer(Engine &);

  virtual void Initialize();
  virtual void Update(GameTime &);

};