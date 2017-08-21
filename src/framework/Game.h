/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

typedef std::unordered_map<const char *, const char *, CStringHash, CStringCompare> EngineComponentsNeededMap;
typedef std::pair<const char *, const char *> EngineComponentsNeededMapPair;
typedef EngineComponentsNeededMap::iterator EngineComponentsNeededMapIter;

class Game {

private:

  const char *name;
  Script *gameScript;

  EngineComponentsNeededMap engineComponentsNeeded;

  Game() {}

public:

  static Game *Load(const char *filename);

  void Initialize();

  void LoadContent();

  void Update(GameTime *gameTime);

  const char *GetName();
  EngineComponentsNeededMap *GetEngineComponentsNeeded();

};