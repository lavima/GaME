/*
File: GameComponent.h
Author: Lars Vidar Magnusson
*/

#ifndef __FRAMEWORK_GAMECOMPONENT__
#define __FRAMEWORK_GAMECOMPONENT__

class Game;
class GameComponent;

typedef std::unordered_map<const char *, GameComponent *, CStringHash, CStringCompare> GameComponentMap;
typedef std::pair<const char *, GameComponentMap *> GameComponentPair;
typedef GameComponentMap::iterator GameComponentMapIter;

class GameComponent {

private:

  Game *game;
  const char *typeName;
  const char *name;

protected:

  GameComponent() {}

public:

  static GameComponent *Create(Game *game, const char *typeName, const char *name);

  Game *GetGame();
  const char *GetName();

  virtual void Initialize() = 0;
  virtual void Update(GameTime *gameTime) = 0;

};

#endif
