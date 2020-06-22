/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;
class EngineComponent;

typedef void (*RegisterAddinFun)(AddinInfo &);

#define ADDINFUN_REGISTERADDIN "RegisterAddin"

class Addin {
private:

    unique_ptr<AddinInfo> info;
    void *handle;

    unordered_map<string, void *> symbolMap;

public:

    static Addin *Load(Platform &platform, const string &filename);

    bool HasSymbol(const string &name);
    void *GetSymbolAddr(const string &name);
    const vector<reference_wrapper<const string>> GetLoadedSymbolNames() const;

    AddinInfo &GetInfo();
    void *GetHandle();

};
