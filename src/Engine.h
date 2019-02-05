/*
File: Engine.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define ENGINE_NAME string("GaME")
#define ENGINE_DESCRIPTION string("GaME Mechanics Engine")
#define ENGINE_VERSION Version(0, 0, 1)

class EngineInfo : public _InfoBase {
    friend class Engine;
    private:

    string executablePath;

    public:

    EngineInfo() : _InfoBase(ENGINE_NAME, ENGINE_DESCRIPTION, ENGINE_VERSION) {}

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
        Platform *platform;

        Log *log;

        Game *game;

        bool isRunning;
        bool isGameRunning;

        void shutdown();

        Engine() {}

    public:

        Engine(Platform &platform, const string &configFilename);
        Engine(Platform &platform, EngineConfig *engineConfig);

        void Initialize();
        void Stop();

        void LoadGame(const string &filename);
        void CloseGame();

        bool LoadAddin(const string &filename);

        void AddComponent(const string &typeName, const string &name);
        void AddComponent(EngineComponent *component);
        EngineComponent *GetComponent(const string &name);

        bool IsRunning();

        const string &GetCommandLine();
        const EngineInfo &GetInfo();
        ScriptEnvironment &GetScriptEnvironment();
        Platform &GetPlatform();
        Game &GetGame();
        Log &GetLog(); 

    private:

        class Scriptable : public _Scriptable {
        public:

            virtual void Register(ScriptEnvironment &environment);

        };

};
