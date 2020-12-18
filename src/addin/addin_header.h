/*
File: AddinHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::addin {

#define EXTENSION_ADDIN ".addin"

#define XMLNAME_ADDINHEADER "Addin"
#define XMLNAME_ADDINHEADER_LIBRARYFILENAME "library"
#define XMLNAME_ADDINHEADER_NAME XMLNAME_INFOBASE_NAME
#define XMLNAME_ADDINHEADER_DESCRIPTION XMLNAME_INFOBASE_DESCRIPTION
#define XMLNAME_ADDINHEADER_VERSION XMLNAME_INFOBASE_VERSION
#define XMLNAME_ADDINHEADER_SYSTEM XMLNAME_SYSTEMVERSIONINFO 
#define XMLNAME_ADDINHEADER_COMPONENT XMLNAME_COMPONENINFO

    enum class GAME_API AddinType : uint32_t {
        System = 1,
        Component = 2
    };

    uint32_t operator&(uint32_t lhs, AddinType rhs);
    uint32_t operator|(uint32_t lhs, AddinType rhs);
    uint32_t operator|(AddinType lhs, AddinType rhs);
    uint32_t& operator<<=(uint32_t& lhs, AddinType rhs);

    class GAME_API AddinHeader : public VersionInfo, public content::XmlContent {

    private:

        AddinType type_;

        std::string library_filename_;

        std::vector<framework::SystemInfo> system_infos_;

        std::vector<framework::ComponentInfo> component_infos_;

    public:

        AddinHeader(const std::string& filename); 
        virtual ~AddinHeader();

        AddinType GetType();

        const std::string& GetLibraryFilename();
        const std::vector<std::reference_wrapper<const framework::SystemInfo>> GetSystemInfos() const;
        const std::vector<std::reference_wrapper<const framework::ComponentInfo>> GetComponentInfos() const;

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

    private:

        class Loader : public content::Content::ILoader {
        private:

            static Loader singleton;

            Loader();

        public:

            content::Content* Load(const std::string& filename) override;

        };

    };

}
