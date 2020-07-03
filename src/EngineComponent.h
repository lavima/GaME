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
class EngineComponent : public Instanceable {
private:

    static unordered_map<string, CreateEngineComponentFun> componentProviders;

    Engine *engine;
        
protected:

    /*
    * Protected constructor to ensure that engine_ components_ must be created through the static Create
    * function
    */
    EngineComponent(Engine &engine, const string &typeName);

public:

    /*
    * Create provides the only way to instantiate engine_ components_.
    */
    static EngineComponent *Create(Engine &engine, const string &typeName);

    /*
    * RegisterProvider must be invoked by all engine_ component implementation providers.
    */
    static void RegisterProvider(const string &typeName, CreateEngineComponentFun createFun);

    /*
    * Initialize is invoked by the engine_ to initialize an engine_ component
    */
    virtual void Initialize() = 0;
    
    /*
    * Update is invoked by the engine on regular intervals
    */
    virtual void Update(GameTime &gameTime) = 0;

    
};
