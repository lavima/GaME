/*
File: Engine.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define ENGINE_NAME new string("GaME")
#define ENGINE_DESCRIPTION new string("GaME Mechanics Engine")
#define ENGINE_VERSION Version::Create(0, 0, 1)

class EngineInfo : public _InfoBase {

public:

    EngineInfo() : _InfoBase(ENGINE_NAME, ENGINE_DESCRIPTION, ENGINE_VERSION) {}

};

/*
* Type definitions used in the Engine class.
*/
typedef std::vector<Addin *> AddinVector;

/*
* The Engine class represents the actual Game Mechanics Engine (GaME). It is a singleton class and all references
* should use the ENGINE and ENGINE_PTR macros for accessing the singleton instance.
*/
class Engine {
private:

    EngineInfo info;

    AddinVector addins;
    EngineComponentMap components;

    const string *executablePath;

    const string *configFilename;
    EngineConfig *config;

    ScriptEnvironment *scriptEnvironment;
    Platform *platform;

    Log *log;

    Game *game;

    bool isRunning;
    bool isGameRunning;

    void shutdown();

public:

    Engine(Platform &platform, EngineConfig &config);

    bool IsRunning();

    ScriptEnvironment &GetScriptEnvironment();

    Platform &GetPlatform();
    Game &GetGame();

    void Initialize();
    void Stop();

    void LoadGame(const string &filename);
    void CloseGame();

    bool LoadAddin(const string &filename);

    void AddComponent(const string &typeName, const string &name);
    void AddComponent(EngineComponent *component);
    EngineComponent *GetComponent(const string &name);

    const string &GetCommandLine();
    const EngineInfo &GetInfo();
  
    Log &GetLog(); 
  
};
