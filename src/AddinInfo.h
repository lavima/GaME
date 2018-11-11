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

    AddinType type;
    const string *libraryFilename;

    EngineComponentInfoMap engineComponents;

    AddinInfo() {}

public:

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

public:

  static EngineComponentInfo *Load(xercesc::DOMElement *element); 

  const string &GetName();
  const string &GetDescription();
  const string &GetVersion();

};
