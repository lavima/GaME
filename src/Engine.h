/*
File: Engine.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define ENGINE Engine::GetSingleton()
#define ENGINE_PTR Engine::GetSingletonPtr()

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

  AddinVector addins;
  EngineComponentMap components;
  
  EngineConfig *engineConfig;
  ScriptEnvironment *scriptEnvironment;

  Game *game;

  bool isRunning;
  bool isGameRunning;

  Engine();

  void shutdown();

public:

  static Engine &GetSingleton();
  static Engine *GetSingletonPtr();

  bool IsRunning();
  ScriptEnvironment &GetScriptEnvironment();
  Game *GetGame();  

  void Initialize(const string &filename); 
  void Stop();

  void LoadGame(const string &filename);
  void CloseGame();

  bool LoadAddin(const string &filename);

  void AddComponent(const string &typeName, const string &name);
  void AddComponent(EngineComponent *component);
  EngineComponent *GetComponent(const string &name);

};