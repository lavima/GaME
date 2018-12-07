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

Version::Version(xml_node &xmlNode) {
    
    assert(string(xmlNode.value()).compare("Version")==0);

    this->major = xmlNode.child("Major").text().as_int();
    this->minor = xmlNode.child("Minor").text().as_int(); 
    this->release = xmlNode.child("Release").text().as_int();

}

Version::Version(xml_node &&xmlNode) {
    
    assert(string(xmlNode.value()).compare("Version")==0);

    this->major = xmlNode.child("Major").text().as_int();
    this->minor = xmlNode.child("Minor").text().as_int(); 
    this->release = xmlNode.child("Release").text().as_int();

}

int Version::GetMajor() const { return major; }
int Version::GetMinor() const { return minor; }
int Version::GetRelease() const { return release; };

const string *Version::GetVersionString() {
    return (const string *)StringUtil::Format("%d-%d-%d", major, minor, release);
}
