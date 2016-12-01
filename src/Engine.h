/*
File: Engine.h
Author: Lars Vidar Magnusson
*/

#ifndef __ENGINE__
#define __ENGINE__

#define ENGINE Engine::GetSingleton()

/*
* Type definitions used in the Engine class.
*/
typedef std::vector<AddinContainer *> AddinVector;
typedef std::unordered_map<const char *, CreateGameComponentFun, CStringHash, CStringCompare> CreateGameComponentMap;
typedef std::pair<const char *, CreateGameComponentFun> CreateGameComponentPair;
typedef CreateGameComponentMap::iterator CreateGameComponentMapIter;

/*
* The Engine class represents the actual Game Mechanics Engine (GaME). It is a singleton class and all references
* should use the ENGINE macro for accessing the singleton instance.
*/
class Engine {

private:

  static Engine *singleton;

  EngineConfig *engineConfig;

  bool isRunning;
  bool isGameRunning;

  ScriptContext *scriptContext;
  Game *game;

  AddinVector addins;

  CreateGameComponentMap createGameComponentMap;

  Engine();

  void shutdown();

public:

  static Engine *GetSingleton();

  bool IsRunning();
  ScriptContext *GetScriptContext();
  Game *GetGame();  

  void Initialize(const char *filename); 
  void Stop();

  void RunGame(const char *filename);
  void CloseGame();

  bool LoadAddin(const char *filename);

  GameComponent *CreateGameComponent(Game *game, const char *typeName, const char *name);

};

#endif
