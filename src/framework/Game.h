/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#ifndef __FRAMEWORK_GAME__
#define __FRAMEWORK_GAME__

class Game {

private:

  const char *name;
  GameComponentMap components;
  Script *gameScript;

  Game() {}

public:

  static Game *Load(const char *filename);

  void Initialize();

  void LoadContent();

  void Update(GameTime *gameTime);

  const char *GetName();
  
  void AddComponent(const char *typeName, const char *name);
  void AddComponent(GameComponent *component);
  GameComponent *GetComponent(const char *name);

};

#endif
