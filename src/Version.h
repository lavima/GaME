/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_VERSION "Version"
#define XMLNAME_VERSION_MAJOR "Major"
#define XMLNAME_VERSION_MINOR "Minor"
#define XMLNAEM_VERSION_RELEASE "Release"

class Version : XMLSerializable {
private:

    int major;
    int minor;
    int release;

    Version() {}

public:

    Version(int major, int minor, int release);
    Version(pugi::xml_node &xmlNode);
    Version(pugi::xml_node &&xmlNode);

    int GetMajor() const;
    int GetMinor() const;
    int GetRelease() const;

    const string *GetVersionString();

    bool operator==(Version &other);

    static bool Load(Version *version, pugi::xml_node &rootNode);
    static bool Save(Version &version, pugi::xml_node *rootNode);

    /* XMLSerializable Interface */

    bool Load(pugi::xml_node &rootNode);
    bool Save(pugi::xml_node *rootNode);

};
