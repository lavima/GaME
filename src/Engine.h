/*
File: Engine.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game {

#define ENGINE_NAME "GaME"
#define ENGINE_DESCRIPTION "GaME Mechanics Engine"
#define ENGINE_VERSION Version(0, 0, 1)


#define ENGINEOPTION_CONFIG "engineConfig"
#define ENGINEOPTION_CONFIG_FILENAME "engineLogFilename"

    /*
    * EngineInfo provides engine_ meta information at runtime. Allthough this class
    * derives from VersionInfo, an XML serializable type, this functionality is never
    * utilized i.e. the information is provided either at compile time or at runtime.
    */
    class GAME_API EngineInfo : public VersionInfo {

        friend class Engine;

    private:

        string executablePath;

    public:

        EngineInfo() : VersionInfo(ENGINE_NAME, ENGINE_DESCRIPTION, ENGINE_VERSION) {}

        const string& GetExecutablePath() const { return executablePath; }

    };

    enum class GAME_API EngineStatus {
        Created = 0,
        Initialized = 1,
        Terminated = 2
    };

    /*
     * The Engine class represents the actual Game Mechanics Engine (GaME).
     */
    class GAME_API Engine {
    private:

        EngineInfo info_;
        EngineStatus status_;

        string config_filename_;
        unique_ptr<EngineConfig> config_;

        vector<addin::Addin*> addins_;
        unordered_map<string, System*> systems_;

        scripting::ScriptEnvironment* script_environment_;
        unique_ptr<platform::Platform> platform_;

        unique_ptr<Log> log_;
        unique_ptr<ofstream> log_file_;

        unique_ptr<framework::Game> game_;

    public:

        Engine();

        bool Initialize();
        void Run();
        void Stop();

        bool LoadGame(const string& filename);
        bool LoadGame(framework::Game& game);
        void UnloadGame();

        bool LoadAddin(const string& filename);

        bool HasSystemType(const string& type_name) const;
        //void AddSystem(const string &name, const string &type_name);
        bool AddSystem(System* system);
        System* GetSystem(const string& name);

        const EngineInfo& GetInfo();
        scripting::ScriptEnvironment& GetScriptEnvironment();
        platform::Platform& GetPlatform();
        framework::Game& GetGame();
        Log& GetLog();

    private:

        void shutdown();

        class Scriptable : public scripting::_Scriptable {
        public:

            virtual void Register(scripting::ScriptEnvironment& environment);

        };

    };
}
