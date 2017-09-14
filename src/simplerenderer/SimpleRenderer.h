/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#pragma once

class SimpleRenderer : public EngineComponent {

public:

  SimpleRenderer(Engine &);

  virtual void Initialize();
  virtual void Update(GameTime &);

};