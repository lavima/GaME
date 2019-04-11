/*
File: AddinInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define EXTENSION_ADDIN "addin"

#define XMLNAME_ADDININFO "Addin"
#define XMLNAME_ADDININFO_LIBRARYFILENAME "libraryFilename"
#define XMLNAME_ADDININFO_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTINFO 

enum AddinType {
    ENGINE_COMPONENT_ADDIN = 1
};

class AddinInfo : public __InfoBase, public XMLData {

private:

    AddinType type;

    string libraryFilename;

    vector<EngineComponentInfo> engineComponents;

    AddinInfo() {}
    
public:

    AddinType GetType();
    
    const string &GetLibraryFilename();
    const vector<reference_wrapper<const EngineComponentInfo>> GetEngineComponents() const;

    bool Load(pugi::xml_node rootNode) override;        
    bool Save(pugi::xml_node rootNode) override;

private:

    class __Factory : public DataFactory {
    private:

        static __Factory singleton;

        __Factory();

    public:

        Data *Load(const string &filename);

    };
  
};
