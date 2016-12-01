/*
File: SimpleRenderer.h
Author: Lars Vidar Magnusson
*/

#ifndef __SIMPLERENDERER_SIMPLERENDERER__
#define __SIMPLERENDERER_SIMPLERENDERER__

class SimpleRenderer : public GameComponent {

public:

  SimpleRenderer(Game *game);

  virtual void Initialize();
  virtual void Update(GameTime *gameTime);

};

#endif
