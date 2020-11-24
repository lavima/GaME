/*
File: System.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

    /*
    * System is the base class for all engine subsystems such as a renderer or audio system. 
    * All systems must be created through the factory pattern provided by this class.
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
        static unordered_map<string, ICreator*>* creators_;
#endif

        Engine* engine_;
        SystemConfig* config_;

    protected:

        /*
        * Protected constructor to ensure that engine components must be created through the static Load
        * function
        */
        System(Engine& engine, SystemConfig& config);

        Engine& GetEngine();

    public:

        /*
        * Load provides the only way to instantiate engine_ components.
        */
        static System* Create(Engine& engine, SystemConfig& config);

        
        /*
        * RegisterType must be invoked by all system implementations
        */
        static void RegisterType(const string& typeName, ICreator* creator);
        
        static bool IsTypeAvailable(const string& type_name);

        /*
        * Initialize is invoked by the engine to initialize an engine component
        */
        virtual bool Initialize() = 0;

        /*
        * Update is invoked by the engine_ on regular intervals
        */
        virtual bool Update(framework::GameTime& gameTime) = 0;

        /*
        * Destroy the engine component
        */
        virtual void Destroy() = 0;

        SystemConfig& GetConfig();

    };

}