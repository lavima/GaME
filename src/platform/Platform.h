/*
File: Platform.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;
class Platform;

typedef Platform *(*CreatePlatformFun)(Engine &, PlatformConfig *);

/*
* This class provides the interface for all platform implementations, and a factory function for 
* creating instance implementations.
*/
class Platform {

private:

    static unordered_map<string, CreatePlatformFun> implementations;

    Engine &engine;

    unordered_map<KeyCode, __InputKeyWritable> inputKeys;

protected:

    Platform(Engine &engine) : engine(engine) {}

public:
    
    static Platform *Create(Engine &engine, PlatformConfig *config);

    virtual bool Initialize() = 0;

    virtual void Shutdown() = 0;

    /*
    * Handle all input events. This should amount in an update of the input state exposed 
    * by this class.
    */
    virtual void HandleEvents() = 0;
    /*
    * Swap display buffers. This is required for all platforms supporting real-time rendering
    */
    virtual void SwapBuffers() = 0;

#ifdef LoadLibrary
#undef LoadLibrary
#endif
    virtual void *LoadLibrary(const string &filename) = 0;

    virtual void UnloadLibrary(void *handle) = 0;

    virtual void *LoadLibrarySymbol(void *handle, const string &name) = 0;

    virtual unsigned long long GetSystemTime() = 0;

    /*
    * Creates a new map with constant reference access to all input keys
    */
    const unordered_map<KeyCode, reference_wrapper<const InputKey>> GetInputKeys();

protected:

    static void RegisterImplementation(const string &name, CreatePlatformFun createFun);

    Engine &GetEngine();
    unordered_map<KeyCode, __InputKeyWritable> GetWritableInputKeys();

};
