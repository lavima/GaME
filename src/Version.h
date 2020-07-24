/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define XMLNAME_VERSION string("Version")
#define XMLNAME_VERSION_MAJOR string("Major")
#define XMLNAME_VERSION_MINOR string("Minor")
#define XMLNAME_VERSION_RELEASE string("Release")

    class GAME_API Version : data::xml::IXmlSerializable {
    private:

        int major_;
        int minor_;
        int release_;


    public:

        Version();
        Version(int major, int minor, int release);
        Version(data::xml::XmlNode node);

        int GetMajor() const;
        int GetMinor() const;
        int GetRelease() const;

        const string* GetVersionString();

        bool operator==(Version& other);

        static bool Load(Version* version, data::xml::XmlNode node);
        static bool Save(Version& version, data::xml::XmlNode node);

        /* XMLSerializable Interface */

        bool Load(data::xml::XmlNode node);
        bool Save(data::xml::XmlNode node);

    };

}