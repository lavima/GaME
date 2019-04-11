/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;
class EngineComponent;

typedef void (*RegisterAddinFun)(AddinInfo &);
typedef EngineComponent *(*CreateEngineComponentFun)(Engine &, const string &, const string &);

#define ADDIN_REGISTERADDIN "RegisterAddin"
#define ADDIN_CREATECOMPONENT "CreateEngineComponent"

class Addin {
private:

    string filename; 
    unique_ptr<AddinInfo> info;
    void *handle;

    unordered_map<string, void *> symbolMap;

public:

    static Addin *Load(const string &filename);

    bool HasSymbol(const string &name);
    void AddSymbol(const string &name, void *address);
    void *GetSymbol(const string &name);

    const string &GetFilename();
    AddinInfo &GetInfo();
    void *GetHandle();
    void SetHandle(void *handle);

};
