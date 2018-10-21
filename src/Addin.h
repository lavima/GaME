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

typedef std::unordered_map<string, void *> SymbolMap;
typedef std::pair<string, void *> SymbolMapPair;

struct Addin {

private:

    const string *filename;
    AddinInfo *info;
    void *handle;

    SymbolMap symbolMap;

    Addin() {}

public:

    ~Addin();

    static Addin *Load(const string &filename);

    bool HasSymbol(const string &name);
    void AddSymbol(const string &name, void *address);
    void *GetSymbol(const string &name);

    const string &GetFilename();
    AddinInfo &GetInfo();
    void *GetHandle();
    void SetHandle(void *handle);

};