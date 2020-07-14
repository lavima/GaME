/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Platform;
class Engine;
class EngineComponent;
class EngineComponentConfig;

typedef void (*RegisterAddinFun)(Engine&, AddinHeader&);
typedef EngineComponent* (*CreateEngineComponentFun)(Engine&, EngineComponentConfig&);
typedef EngineComponentConfig* (*LoadEngineComponentConfigFun)(XmlNode);
typedef bool (*SaveEngineComponentConfigFun)(EngineComponentConfig&, XmlNode);

#define ADDINFUN_REGISTERADDIN "RegisterAddin"
#define ADDINFUN_ENGINECOMPONENT_CREATE string("CreateEngineComponent")
#define ADDINFUN_ENGINECOMPONENTCONFIG_LOAD "LoadEngineComponentConfig" 
#define ADDINFUN_ENGINECOMPONENTCONFIG_SAVE "SaveEngineComponentConfig" 

/*
* Addin provides functionality for importing functionality. 
*/
class Addin {
private:

    void* handle_;

    unique_ptr<AddinHeader> header_;
    
    unordered_map<string, void *> symbol_map_;

    Addin(AddinHeader* header) : handle_(nullptr), header_(unique_ptr<AddinHeader>(header)) {}

public:

    static Addin *Load(Engine& engine, const string &filename);

    bool HasSymbol(const string &name);
    void *GetSymbolAddr(const string &name);
    const vector<reference_wrapper<const string>> GetLoadedSymbolNames() const;

    AddinHeader &GetHeader();
    void *GetHandle();

    AddinType GetType() const;

};
