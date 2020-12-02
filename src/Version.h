/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define XMLNAME_VERSION std::string("Version")
#define XMLNAME_VERSION_MAJOR std::string("Major")
#define XMLNAME_VERSION_MINOR std::string("Minor")
#define XMLNAME_VERSION_RELEASE std::string("Release")

    class GAME_API Version : content::xml::IXmlSerializable {
    private:

        int major_;
        int minor_;
        int release_;


    public:

        Version();
        Version(int major, int minor, int release);
        Version(content::xml::XmlNode node);

        int GetMajor() const;
        int GetMinor() const;
        int GetRelease() const;

        const std::string* GetVersionString();

        bool operator==(Version& other);

        static bool Load(Version* version, content::xml::XmlNode node);
        static bool Save(Version& version, content::xml::XmlNode node);

        /* XMLSerializable Interface */

        bool Load(content::xml::XmlNode node);
        bool Save(content::xml::XmlNode node);

    };

}
