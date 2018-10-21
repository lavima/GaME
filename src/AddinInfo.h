/*
File: AddinInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum AddinType {
    ENGINE_COMPONENT_ADDIN = 1
};

class EngineComponentInfo;

typedef std::unordered_map<string, EngineComponentInfo *> EngineComponentInfoMap;
typedef std::pair<string, EngineComponentInfo *> EngineComponentInfoPair;
typedef EngineComponentInfoMap::iterator EngineComponentInfoMapIter;

class AddinInfo {

    friend class Engine;

private:

    AddinType addinType;

    const string *name;
    const string *description;
    
    const Version *version;
    
    const string *filename;
    const string *libraryFilename;

    EngineComponentInfoMap engineComponents;

    AddinInfo() {}
    
public:

    ~AddinInfo();

    static AddinInfo *Load(const string &filename);

    AddinType GetType();
    
    const string &GetName();
    const string &GetDescription();
    
    const Version &GetVersion();
    
    const string &GetFilename();
    const string &GetLibraryFilename();
    
    const EngineComponentInfoMap &GetEngineComponents();
  
};

class EngineComponentInfo {

    friend class AddinInfo;

private:

    const string *typeName;
    const string *description;
    const Version *version;

public:

    ~EngineComponentInfo();

    const string &GetTypeName();
    const string &GetDescription();
    const Version &GetVersion();

};