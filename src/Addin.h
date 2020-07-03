/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Platform;
class Engine;
class EngineComponent;
class EngineComponentConfig;

typedef void (*RegisterAddinFun)(AddinHeader &);
typedef EngineComponent* (*CreateEngineComponentFun)(Engine&, const string&);
typedef EngineComponentConfig* (*LoadEngineComponentConfigFun)(const string&, XmlNode);
typedef void (*SaveEngineComponentConfigFun)(const string&, EngineComponentConfig&, XmlNode);

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

    Addin(AddinHeader* header) : header_(unique_ptr<AddinHeader>(header)) {}

public:

    static Addin *Load(Platform &platform, const string &filename);

    bool HasSymbol(const string &name);
    void *GetSymbolAddr(const string &name);
    const vector<reference_wrapper<const string>> GetLoadedSymbolNames() const;

    AddinHeader &GetHeader();
    void *GetHandle();

    AddinType GetType() const;

};
