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
    protected:

        class Creator {
        public:
            virtual System* Create(Engine& engine, SystemConfig& config) = 0;
        };

    private:

        static unordered_map<string, Creator*> system_providers_;

        Engine* engine_;
        SystemConfig* config_;

    protected:

        /*
        * Protected constructor to ensure that engine_ components must be created through the static Create
        * function
        */
        System(Engine& engine, SystemConfig& config);

        Engine& GetEngine();
        SystemConfig& GetConfig();

    public:

        /*
        * Create provides the only way to instantiate engine_ components.
        */
        static System* Create(Engine& engine, SystemConfig& config);

        
        /*
        * RegisterProvider must be invoked by all engine_ component implementation providers.
        */
        static void RegisterProvider(const string& typeName, Creator* creator);
        
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

    

    };

}