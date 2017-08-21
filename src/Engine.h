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

/*
* The Engine class represents the actual Game Mechanics Engine (GaME). It is a singleton class and all references
* should use the ENGINE macro for accessing the singleton instance.
*/
class Engine {
private:

  static Engine *singleton;

  EngineConfig *engineConfig;
  ScriptEnvironment *scriptEnvironment;

  bool isRunning;
  bool isGameRunning;

  Game *game;
  AddinVector addins;

  EngineComponentMap components;
  

  Engine();

  void shutdown();

public:

  static Engine *GetSingleton();

  bool IsRunning();
  ScriptEnvironment *GetScriptEnvironment();
  Game *GetGame();  

  void Initialize(const char *filename); 
  void Stop();

  void LoadGame(const char *filename);
  void CloseGame();

  bool LoadAddin(const char *filename);

  void AddComponent(const char *typeName, const char *name);
  void AddComponent(EngineComponent *component);
  EngineComponent *GetComponent(const char *name);

};

#endif
