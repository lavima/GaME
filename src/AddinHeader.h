/*
File: AddinHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define EXTENSION_ADDIN "addin"

#define XMLNAME_ADDININFO "Addin"
#define XMLNAME_ADDININFO_LIBRARYFILENAME "library"
#define XMLNAME_ADDININFO_NAME XMLNAME_INFOBASE_NAME
#define XMLNAME_ADDININFO_DESCRIPTION XMLNAME_INFOBASE_DESCRIPTION
#define XMLNAME_ADDININFO_VERSION XMLNAME_INFOBASE_VERSION
#define XMLNAME_ADDININFO_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTINFO 

enum class AddinType {
    EngineComponent = 1
};

class AddinHeader : public VersionInfo, public XmlData {

private:

    AddinType type_;

    string library_filename_;

    vector<EngineComponentVersionInfo> engine_components_;

public:

    AddinHeader(const string &filename) : XmlData(filename), type_(AddinType::EngineComponent) {}

    AddinType GetType();
    
    const string &GetLibraryFilename();
    const vector<reference_wrapper<const EngineComponentVersionInfo>> GetEngineComponents() const;

    bool Load(XmlNode root_node) override;        
    bool Save(XmlNode root_node) override;

private:

    class Loader : public DataLoader {
    private:

        static Loader singleton;

        Loader();

    public:

        Data *Load(const string &filename);

    };
  
};
