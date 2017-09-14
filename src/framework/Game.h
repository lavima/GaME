/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

typedef unordered_map<string, const string> EngineComponentsNeededMap;
typedef pair<string, const string> EngineComponentsNeededMapPair;
typedef EngineComponentsNeededMap::iterator EngineComponentsNeededMapIter;

class Game {

private:

  const string *name;
  Script *gameScript;

  EngineComponentsNeededMap engineComponentsNeeded;

  Game() {}

public:

  static Game *Load(const string &filename);

  void Initialize();

  void LoadContent();
  void UnloadContent();

  void Update(GameTime &gameTime);

  const string &GetName();
  EngineComponentsNeededMap &GetEngineComponentsNeeded();

};