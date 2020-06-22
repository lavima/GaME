/*
File: Engine.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define ENGINE_NAME "GaME"
#define ENGINE_DESCRIPTION "GaME Mechanics Engine"
#define ENGINE_VERSION Version(0, 0, 1)


#define ENGINE_OPTION_CONFIG "engineConfig"
#define ENGINE_OPTION_CONFIG "engineLogFilename"

class EngineInfo : public __InfoBase {
    friend class Engine;
    private:

    string executablePath;

    public:

    EngineInfo() : __InfoBase(ENGINE_NAME, ENGINE_DESCRIPTION, ENGINE_VERSION) {}

    const string &GetExecutablePath() const { return executablePath; }

};

/*
 * The Engine class represents the actual Game Mechanics Engine (GaME). 
 */
class Engine {
    private:

        EngineInfo info;
        string configFilename;
        EngineConfig *config;

        vector<Addin *> addins;
        unordered_map<string, EngineComponent *> components;

        ScriptEnvironment *scriptEnvironment;
        unique_ptr<Platform> platform;

        unique_ptr<Log> log;
        unique_ptr<ofstream> logFileStream;

        unique_ptr<Game> game;

        bool isRunning;
        bool isGameRunning;

    public:

        Engine();

        void Initialize();
        void Stop();

        void LoadGame(const string &filename);
        void CloseGame();

        bool LoadAddin(const string &filename);

        void AddComponent(const string &typeName, const string &name);
        void AddComponent(EngineComponent *component);
        EngineComponent *GetComponent(const string &name);

        bool IsRunning();

        const EngineInfo &GetInfo();
        ScriptEnvironment &GetScriptEnvironment();
        Platform &GetPlatform();
        Game &GetGame();
        Log &GetLog(); 

    private:

        void shutdown(); 

        class Scriptable : public _Scriptable {
        public:

            virtual void Register(ScriptEnvironment &environment);

        };

};
