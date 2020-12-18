/*
File: VersionInfo.cpp
Author: Lars Vidar Magnusson
 */

#include <string>
#include <sstream>
#include <memory>
#include <cassert>
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
#include "version_info.h"

namespace game {

    VersionInfo::VersionInfo(const std::string& xml_element_name) : xml_element_name_(xml_element_name) {}

    VersionInfo::VersionInfo(const std::string& name, const Version& version) {

        name_ = name;
        description_ = "";
        version_ = version;

        xml_element_name_ = XMLNAME_VERSIONINFO;
    }

    VersionInfo::VersionInfo(const std::string& name, const std::string& description, const Version& version) {

        name_ = name;
        description_ = description;
        version_ = version;

        xml_element_name_ = XMLNAME_VERSIONINFO;

    }

    VersionInfo::VersionInfo(const std::string&& name, const std::string&& description, const Version&& version) {

        name_ = name;
        description_ = description;
        version_ = version;

        xml_element_name_ = XMLNAME_VERSIONINFO;

    }

    VersionInfo::VersionInfo(content::xml::XmlNode xml_node, const std::string& xml_element_name) {

        xml_element_name_ = xml_element_name;

        assert(this->Load(xml_node));

    }

    VersionInfo::VersionInfo(const VersionInfo& other) {
      name_ = other.name_;
      description_ = other.description_;
      version_ = other.version_;
    }


    bool VersionInfo::Load(VersionInfo* info, content::xml::XmlNode root_node) {

        if (root_node.GetName()!=info->xml_element_name_)
            return false;

        content::xml::XmlNode name_node = root_node.GetChild(XMLNAME_INFOBASE_NAME);
        if (!name_node)
            return false;
        info->name_ = std::string(name_node.GetValue());

        content::xml::XmlNode description_node = root_node.GetChild(XMLNAME_INFOBASE_DESCRIPTION);
        // Description is optional
        if (description_node)
            info->description_ = std::string(description_node.GetValue());

        return info->version_.Load(root_node.GetChild(XMLNAME_INFOBASE_VERSION));

    }

    bool VersionInfo::Save(VersionInfo& info, content::xml::XmlNode root_node) {

        if (info.xml_element_name_!="")
            root_node.SetName(info.xml_element_name_);

        content::xml::XmlNode name_node = root_node.AddChild(XMLNAME_INFOBASE_NAME);
        name_node.SetValue(info.name_);

        content::xml::XmlNode description_node = root_node.AddChild(XMLNAME_INFOBASE_DESCRIPTION);
        description_node.SetValue(info.description_);

        content::xml::XmlNode version_node = root_node.AddChild();
        return info.version_.Save(version_node);

    }

    const std::string& VersionInfo::GetName() const { return name_; }
    void VersionInfo::SetName(const std::string& name) { this->name_ = name; }

    const std::string& VersionInfo::GetDescription() const { return description_; }
    void VersionInfo::SetDescription(const std::string& description) { this->description_ = description; }

    const Version& VersionInfo::GetVersion() const { return this->version_; }
    void VersionInfo::SetVersion(const Version& version) { this->version_ = version; }

    bool VersionInfo::Load(content::xml::XmlNode root_node) { return VersionInfo::Load(this, root_node); }
    bool VersionInfo::Save(content::xml::XmlNode root_node) { return VersionInfo::Save(*this, root_node); }

}
