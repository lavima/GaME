/*
File: Platform.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

class Engine;
class Platform;

typedef Platform *(*CreatePlatformFun)(PlatformConfig &);

typedef unordered_map<string, CreatePlatformFun> CreatePlatformMap;
typedef pair<string, CreatePlatformFun> CreatePlatformPair;

/*
* This class provides the interface for all platform implementations, and a factory function for 
* creating instance implementations.
*/
class Platform {


public:
    
    static Platform *Create(PlatformConfig &config);

    virtual bool Initialize(PlatformConfig &config) = 0;

    virtual void Shutdown() = 0;

    virtual void HandleEvents() = 0;

    virtual void SwapBuffers() = 0;

#ifdef LoadLibrary
#undef LoadLibrary
#endif
    virtual void *LoadLibrary(const string &filename) = 0;

    virtual void UnloadLibrary(void *handle) = 0;

    virtual void *LoadLibrarySymbol(void *handle, const string &name) = 0;

    virtual unsigned long long GetSystemTime() = 0;

#ifdef GetCommandLine
#undef GetCommandLine
#endif
    virtual const string &GetCommandLine() = 0;

protected:

    static void RegisterImplementation(const string &typeName, CreatePlatformFun createFun);

private:

    static CreatePlatformMap implementations;

};