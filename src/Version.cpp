/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

namespace game {

    Version::Version() {
        this->major_ = 0;
        this->minor_ = 0;
        this->release_ = 0;
    }
    Version::Version(int major, int minor, int release) {

        this->major_ = major;
        this->minor_ = minor;
        this->release_ = release;

    }
    Version::Version(data::xml::XmlNode node) {
        Version::Load(this, node);
    }


    int Version::GetMajor() const { return major_; }
    int Version::GetMinor() const { return minor_; }
    int Version::GetRelease() const { return release_; };

    const string* Version::GetVersionString() {
        return (const string*)lib::StringUtil::Create("%d-%d-%d", major_, minor_, release_);
    }

    bool Version::operator==(Version& other) { return major_==other.major_&&minor_==other.minor_&&release_==other.release_; }

    bool Version::Load(Version* version, data::xml::XmlNode root_node) {

        if (root_node.GetName()!=XMLNAME_VERSION)
            return false;

        data::xml::XmlNode major_node = root_node.GetChild(XMLNAME_VERSION_MAJOR);
        if (!major_node)
            return false;
        version->major_ = stoi(major_node.GetValue());

        data::xml::XmlNode minor_node = root_node.GetChild(XMLNAME_VERSION_MINOR);
        if (!minor_node)
            return false;
        version->minor_ = stoi(minor_node.GetValue());

        data::xml::XmlNode release_node = root_node.GetChild(XMLNAME_VERSION_RELEASE);
        if (!release_node)
            return false;
        version->release_ = stoi(release_node.GetValue());

        return true;

    }

    bool Version::Save(Version& version, data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_VERSION);

        data::xml::XmlNode major_node = root_node.AddChild();
        major_node.SetName(XMLNAME_VERSION_MAJOR);
        major_node.SetValue(to_string(version.major_));

        data::xml::XmlNode minor_node = root_node.AddChild();
        minor_node.SetName(XMLNAME_VERSION_MINOR);
        minor_node.SetValue(to_string(version.minor_));

        data::xml::XmlNode release_node = root_node.AddChild();
        release_node.SetName(XMLNAME_VERSION_RELEASE);
        release_node.SetValue(to_string(version.release_));

        return true;

    }

    bool Version::Load(data::xml::XmlNode root_node) { return Version::Load(this, root_node); }
    bool Version::Save(data::xml::XmlNode root_node) { return Version::Save(*this, root_node); }

}