/*
File: System.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    /*
    * System is the base class for all engine subsystems such as a renderer or audio system. 
    * Trace systems must be created through the factory pattern provided by this class.
    */
    class GAME_API System {
        friend class addin::ISystemProvider;

    protected:

        class ICreator {
        public:
            virtual System* Create(Engine& engine, SystemConfig& config) = 0;
        };

    private:

#ifndef DLL_BUILD
        static std::unordered_map<std::string, ICreator*>* creators_;
#endif

        Engine* engine_;

        SystemInfo info_;
        SystemConfig* config_;

    protected:

        /*
        * Protected constructor to ensure that engine components must be created through the static Load
        * function
        */
        System(Engine& engine, const SystemInfo& info, SystemConfig& config);

        Engine& GetEngine();

    public:

        /*
        * Load provides the only way to instantiate engine_ components.
        */
        static System* Create(Engine& engine, SystemConfig& config);

        
        /*
        * RegisterType must be invoked by all system implementations
        */
        static void RegisterType(const std::string& typeName, ICreator* creator);
        
        static bool IsTypeAvailable(const std::string& type_name);

        /*
        * Initialize is invoked by the engine to initialize a system
        */
        virtual bool Initialize() = 0;

        virtual void GameLoaded(Game& game) = 0;
        virtual void GameStarted(Game& game) = 0;

        /*
        * Update is invoked by the engine on regular intervals
        */
        virtual bool Update(framework::GameTime& gameTime) = 0;

        /*
        * Destroy the engine component
        */
        virtual void Destroy() = 0;

        const SystemInfo& GetInfo() const;
        SystemConfig& GetConfig();

    };

}