/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define TYPENAME_SIMPLERENDERER "SimpleRenderer"

class SimpleRenderer : public EngineComponent {

private:

    VkInstance vkInstance;
    VkApplicationInfo vkAppInfo;

public:

  SimpleRenderer(Engine &);

  virtual void Initialize();
  virtual void Update(GameTime &);

};