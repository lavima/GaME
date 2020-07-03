/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_VERSION string("Version")
#define XMLNAME_VERSION_MAJOR string("Major")
#define XMLNAME_VERSION_MINOR string("Minor")
#define XMLNAME_VERSION_RELEASE string("Release")

class Version : XmlSerializable {
private:

    int major_;
    int minor_;
    int release_;


public:

    Version();
    Version(int major, int minor, int release);
    Version(XmlNode node);

    int GetMajor() const;
    int GetMinor() const;
    int GetRelease() const;

    const string *GetVersionString();

    bool operator==(Version &other);

    static bool Load(Version *version, XmlNode node);
    static bool Save(Version &version, XmlNode node);

    /* XMLSerializable Interface */

    bool Load(XmlNode node);
    bool Save(XmlNode node);

};
