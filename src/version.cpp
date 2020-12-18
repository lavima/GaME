/*
File: Version.h
Author: Lars Vidar Magnusson
*/

#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include <pugixml.hpp>

#include "global.h"
#include "lib/format.h"
#include "content/xml/xml_range.h"
#include "content/xml/xml_attribute.h"
#include "content/xml/xml_node.h"
#include "content/xml/xml_document.h"
#include "content/xml/xml_serializable.h"
#include "version.h"

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
    Version::Version(content::xml::XmlNode node) {
        Version::Load(this, node);
    }


    int Version::GetMajor() const { return major_; }
    int Version::GetMinor() const { return minor_; }
    int Version::GetRelease() const { return release_; }

    const std::string* Version::GetVersionString() {
        return (const std::string*)lib::format::Format::string("%0-%1-%2", major_, minor_, release_);
    }

    bool Version::operator==(Version& other) { return major_==other.major_&&minor_==other.minor_&&release_==other.release_; }

    bool Version::Load(Version* version, content::xml::XmlNode root_node) {

        if (root_node.GetName()!=XMLNAME_VERSION)
            return false;

        content::xml::XmlNode major_node = root_node.GetChild(XMLNAME_VERSION_MAJOR);
        if (!major_node)
            return false;
        version->major_ = stoi(major_node.GetValue());

        content::xml::XmlNode minor_node = root_node.GetChild(XMLNAME_VERSION_MINOR);
        if (!minor_node)
            return false;
        version->minor_ = stoi(minor_node.GetValue());

        content::xml::XmlNode release_node = root_node.GetChild(XMLNAME_VERSION_RELEASE);
        if (!release_node)
            return false;
        version->release_ = stoi(release_node.GetValue());

        return true;

    }

    bool Version::Save(Version& version, content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_VERSION);

        content::xml::XmlNode major_node = root_node.AddChild();
        major_node.SetName(XMLNAME_VERSION_MAJOR);
        major_node.SetValue(std::to_string(version.major_));

        content::xml::XmlNode minor_node = root_node.AddChild();
        minor_node.SetName(XMLNAME_VERSION_MINOR);
        minor_node.SetValue(std::to_string(version.minor_));

        content::xml::XmlNode release_node = root_node.AddChild();
        release_node.SetName(XMLNAME_VERSION_RELEASE);
        release_node.SetValue(std::to_string(version.release_));

        return true;

    }

    bool Version::Load(content::xml::XmlNode root_node) { return Version::Load(this, root_node); }
    bool Version::Save(content::xml::XmlNode root_node) { return Version::Save(*this, root_node); }

}
