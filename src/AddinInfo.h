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

class AddinInfo : public _InfoBase {

    // TODO still needed? 
    friend class Engine;

private:

    AddinType addinType;

    const string *filename;
    const string *libraryFilename;

    EngineComponentInfoMap engineComponents;

    AddinInfo() {}
    
public:

    ~AddinInfo();

    static AddinInfo *Load(const string &filename);

    AddinType GetType();
    
    const string &GetFilename();
    const string &GetLibraryFilename();
    
    const EngineComponentInfoMap &GetEngineComponents();
  
};

class EngineComponentInfo : public _InfoBase {

    friend class AddinInfo;

public:

    ~EngineComponentInfo();

    static AddinInfo *Load(pugi::xml_node &element);

};
