/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Version {
private:

    int major;
    int minor;
    int release;

    Version(int major, int minor, int release);

public:

    static Version *Create(int major, int minor, int release);
    static Version *Load(pugi::xml_node &element);

    const int GetMajor() const;
    const int GetMinor() const;
    const int GetRelease() const;

    const string *GetVersionString();

};
