/*
File: AddinHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define EXTENSION_ADDIN "addin"

#define XMLNAME_ADDININFO "Addin"
#define XMLNAME_ADDININFO_LIBRARYFILENAME "library"
#define XMLNAME_ADDININFO_NAME XMLNAME_INFOBASE_NAME
#define XMLNAME_ADDININFO_DESCRIPTION XMLNAME_INFOBASE_DESCRIPTION
#define XMLNAME_ADDININFO_VERSION XMLNAME_INFOBASE_VERSION
#define XMLNAME_ADDININFO_ENGINECOMPONENT XMLNAME_SYSTEMVERSIONINFO 

    enum class GAME_API AddinType {
        EngineComponent = 1
    };

    class GAME_API AddinHeader : public VersionInfo, public data::XmlData {

    private:

        AddinType type_;

        string library_filename_;

        vector<SystemVersionInfo> engine_components_;

    public:

        AddinHeader(const string& filename) : data::XmlData(filename), type_(AddinType::EngineComponent) {}

        AddinType GetType();

        const string& GetLibraryFilename();
        const vector<reference_wrapper<const SystemVersionInfo>> GetEngineComponents() const;

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

    private:

        class Loader : public data::Data::DataLoader {
        private:

            static Loader singleton;

            Loader();

        public:

            data::Data* Load(const string& filename);

        };

    };

}