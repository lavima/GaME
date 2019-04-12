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
Version::Version(pugi::xml_node &xmlNode) {
    Version::Load(this, xmlNode);
}
Version::Version(pugi::xml_node &&xmlNode) { 
    Version::Load(this, xmlNode);
}

int Version::GetMajor() const { return major; }
int Version::GetMinor() const { return minor; }
int Version::GetRelease() const { return release; };

const string *Version::GetVersionString() {
    return (const string *)StringUtil::Format("%d-%d-%d", major, minor, release);
}

bool Version::operator==(Version &other) { return major==other.major && minor==other.minor && release==other.release; }

bool Version::Load(Version *version, pugi::xml_node rootNode) {

    if (string(rootNode.value()).compare(XMLNAME_VERSION))
        return false;

    xml_node majorNode = rootNode.child(XMLNAME_VERSION_MAJOR);
    if (!majorNode)
        return false;
    version->major = majorNode.text().as_int();

    xml_node minorNode = rootNode.child(XMLNAME_VERSION_MINOR)
    if (!minorNode)
        return false;
    version->minor = minorNode.text().as_int(); 

    xml_node releaseNode = rootNode.child(XMLNAME_VERSION_RELEASE)
    if (!releaseNode)
        return false;
    version->release = releaseNode.text().as_int();

    return true;

}

bool Version::Save(Version &version, pugi::xml_node rootNode) {

    rootNode.set_name(XMLNAME_VERSION);

    xml_node majorNode = rootNode.append_child();
    majorNode.set_name(XMLNAME_VERSION_MAJOR);
    majorNode.set_value(to_string(version.major));
    
    xml_node minorNode = rootNode.append_child();
    minorNode.set_name(XMLNAME_VERSION_MINOR);
    minorNode.set_value(to_string(version.minor));

    xml_node releaseNode = rootNode.append_child();
    releaseNode.set_name(XMLNAME_VERSION_RELEASE);
    releaseNode.set_value(to_string(version.release));

    return true;

}

bool Version::Load(pugi::xml_node rootNode) { return Version::Load(this, rootNode); }
bool Version::Save(pugi::xml_node rootNode) { return Version::Save(*this, rootNode); }
