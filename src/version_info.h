/*
File: VersionInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define XMLNAME_VERSIONINFO "Version"
#define XMLNAME_INFOBASE_NAME "Name"
#define XMLNAME_INFOBASE_DESCRIPTION "Description"
#define XMLNAME_INFOBASE_VERSION XMLNAME_VERSION 

    /*
    * VersionInfo contains information that is used to specify type information. The class
    * is XML serializable. The class is also a base class for other classes that provide version
    * information.
    */
    class GAME_API VersionInfo : public content::xml::IXmlSerializable {
    private:

        std::string name_;
        std::string description_;
        Version version_;

        std::string xml_element_name_;

    protected:

        VersionInfo(const std::string& xml_element_name = XMLNAME_VERSIONINFO);
        VersionInfo(const std::string& name, const Version& version);
        VersionInfo(const std::string& name, const std::string& description, const Version& version);
        VersionInfo(const std::string&& name, const std::string&& description, const Version&& version);
        VersionInfo(content::xml::XmlNode xml_node, const std::string& xml_element_name = XMLNAME_VERSIONINFO);

        static bool Load(VersionInfo* info, content::xml::XmlNode root_node);
        static bool Save(VersionInfo& info, content::xml::XmlNode root_node);

        void SetName(const std::string& name);
        void SetDescription(const std::string& description);
        void SetVersion(const Version& version);

    public:

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

        const std::string& GetName() const;
        const std::string& GetDescription() const;
        const Version& GetVersion() const;

    };

}
