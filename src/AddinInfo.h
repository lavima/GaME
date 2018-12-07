/*
File: AddinInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum AddinType {
    ENGINE_COMPONENT_ADDIN = 1
};

class EngineComponentInfo;

class AddinInfo : public _InfoBase {

    // TODO still needed? 
    friend class Engine;

private:

    AddinType type;

    string filename;
    string libraryFilename;

    unordered_map<string, EngineComponentInfo *> engineComponents;

    AddinInfo() {}
    
public:

    AddinInfo(pugi::xml_document &xmlDocument);
    ~AddinInfo();

    AddinType GetType();
    
    const string &GetFilename();
    const string &GetLibraryFilename();
    
    const unordered_map<string, EngineComponentInfo *> &GetEngineComponents() const;
  
};

class EngineComponentInfo : public _InfoBase {

    friend class AddinInfo;

public:

    EngineComponentInfo(pugi::xml_node &xmlNode);
    ~EngineComponentInfo();


};
