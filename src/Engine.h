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

        std::string executablePath;

    public:

        EngineInfo() : VersionInfo(ENGINE_NAME, ENGINE_DESCRIPTION, ENGINE_VERSION) {}

        const std::string& GetExecutablePath() const { return executablePath; }

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

        std::string config_filename_;
        std::unique_ptr<EngineConfig> config_;

        std::vector<addin::Addin*> addins_;
        
        std::unordered_map<std::string, std::unique_ptr<framework::System>> systems_;

        std::unordered_map<std::string, framework::System*> systems_by_type_;

        std::unordered_map<std::string, std::vector<std::reference_wrapper<framework::Component>>> components_by_name_;
        std::unordered_map<std::string, std::vector<std::reference_wrapper<framework::Component>>> components_by_type_;

        scripting::ScriptEnvironment* script_environment_;
        std::unique_ptr<platform::Platform> platform_;

        Log* log_;
        std::unique_ptr<std::ofstream> log_file_;

        std::unique_ptr<framework::Game> game_;

    public:

        Engine();

        bool Initialize();
        void Run();
        void Stop();

        bool LoadGame(const std::string& filename);
        bool LoadGame(framework::Game& game);
        void UnloadGame();

        bool LoadAddin(const std::string& filename);

        bool HasSystemType(const std::string& type_name) const;

        bool LoadSystem(framework::SystemConfig& system_config);
        
        std::optional<std::reference_wrapper<framework::System>> GetSystemByName(const std::string& name);
        std::optional<std::reference_wrapper<framework::System>> GetSystemByType(const std::string& type_name);

        std::optional<const std::vector<std::reference_wrapper<framework::Component>>> GetComponentsByName(const std::string& name);
        std::optional<const std::vector<std::reference_wrapper<framework::Component>>> GetComponentsByType(const std::string& type_name);

        const EngineInfo& GetInfo();
        scripting::ScriptEnvironment& GetScriptEnvironment();
        platform::Platform& GetPlatform();
        framework::Game& GetGame();
        Log& GetLog();

    private:

        void UpdateComponentsCache();

        void shutdown();

        class Scriptable : public scripting::_Scriptable {
        public:

            virtual void Register(scripting::ScriptEnvironment& environment);

        };

    };
}
