/*
File: Engine.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Type definitions used in the Engine class.
*/
typedef std::vector<AddinContainer *> AddinVector;

class Engine;

struct EngineInfo {

    const string Name = "GaME";
    const int MajorVersion = 0;
    const int MinorVersion = 0;
    const int Release = 1;

    const string &GetVersionString() { return versionString; }

    string ExecutablePath;
    string ConfigFilename;

private:

    const string versionString = StringUtil::Format("%d-%d-%d", MajorVersion, MinorVersion, Release);   

};

/*
* The Engine class represents the actual Game Mechanics Engine (GaME). It is a singleton class and all references
* should use the ENGINE and ENGINE_PTR macros for accessing the singleton instance.
*/
class Engine {
private:

    EngineInfo info;

    AddinVector addins;
    EngineComponentMap components;

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
    Game *GetGame();

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
