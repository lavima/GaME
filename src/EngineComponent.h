/*
File: EngineComponent.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* EngineComponent is the base class for all engine_ components_ i.e. engine_ subsystems such as a renderer 
* or audio system. All engine_ components_ must be created through the factory pattern provided by this 
* class.
*/
class EngineComponent {
private:

    static unordered_map<string, CreateEngineComponentFun> component_providers_;

    Engine* engine_;
    EngineComponentConfig* config_;
        
protected:

    /*
    * Protected constructor to ensure that engine_ components must be created through the static Create
    * function
    */
    EngineComponent(Engine &engine, EngineComponentConfig& config);

    Engine& GetEngine();
    EngineComponentConfig& GetConfig();

public:


    /*
    * Create provides the only way to instantiate engine_ components.
    */
    static EngineComponent *Create(Engine &engine, EngineComponentConfig& config);

    /*
    * RegisterProvider must be invoked by all engine_ component implementation providers.
    */
    static void RegisterProvider(const string &typeName, CreateEngineComponentFun createFun);

    /*
    * Initialize is invoked by the engine_ to initialize an engine_ component
    */
    virtual bool Initialize() = 0;
    
    /*
    * Update is invoked by the engine_ on regular intervals
    */
    virtual void Update(GameTime &gameTime) = 0;

    /*
    * Destroy the engine component
    */
    virtual void Destroy() = 0;

    
};
