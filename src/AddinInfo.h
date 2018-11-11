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

class AddinInfo : public InfoBase {

    // TODO still needed? 
    friend class Engine;

private:

<<<<<<< HEAD
    AddinType type;
    const string *libraryFilename;

    EngineComponentInfoMap engineComponents;

    AddinInfo() {}
=======
    AddinType addinType;

    const string *name;
    const string *description;
    
    const Version *version;
    
    const string *filename;
    const string *libraryFilename;

    EngineComponentInfoMap engineComponents;
>>>>>>> 2792e9c4014905c812354151c7218ff58293030d

    AddinInfo() {}
    
public:

<<<<<<< HEAD
    static AddinInfo *Load(const string &filename);

    AddinType GetType();
    const string &GetLibraryFilename();
    const EngineComponentInfoMap &GetEngineComponents();

};

class EngineComponentInfo {
private:

    const string *name;
    const string *description;
    const string *version;

    EngineComponentInfo() {}
=======
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
>>>>>>> 2792e9c4014905c812354151c7218ff58293030d

public:

    ~EngineComponentInfo();

    const string &GetTypeName();
    const string &GetDescription();
    const Version &GetVersion();

};
