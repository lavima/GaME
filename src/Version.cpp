/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

Version::Version(int major, int minor, int release) {
    this->major = major;
    this->minor = minor;
    this->release = release;
}

Version *Version::Create(int major, int minor, int release) {
    return new Version(major, minor, release);
}

Version *Version::Load(xml_node &element) {
    
    if (string(element.value()).compare("Version")!=0)
        return nullptr;

    return Create(element.child("Major").value(), element.child("Minor").value(), element.child("Version").value());

}

const int Version::GetMajor() const { return major; }
const int Version::GetMinor() const { return minor; }
const int Version::GetRelease() const { return release; };

const string *Version::GetVersionString() {
    return (const string *)StringUtil::Format("%d-%d-%d", major, minor, release);
}
