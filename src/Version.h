/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Version {
  friend class _InfoBase;
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

};
