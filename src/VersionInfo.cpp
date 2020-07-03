/*
File: VersionInfo.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

VersionInfo::VersionInfo(const string& name, const Version& version) {

    name_ = name;
    version_ = version;

}

VersionInfo::VersionInfo(const string &name, const string &description, const Version &version) {

    name_ = name;
    description_ = description;
    version_ = version;

}

VersionInfo::VersionInfo(const string &&name, const string &&description, const Version &&version) {

    this->name_ = name;
    this->description_ = description;
    this->version_ = version;

}

VersionInfo::VersionInfo(XmlNode xml_node) { assert(this->Load(xml_node)); }

bool VersionInfo::Load(VersionInfo *info, XmlNode root_node) {

    XmlNode name_node = root_node.GetChild(XMLNAME_INFOBASE_NAME);
    if (!name_node)
        return false;
    info->name_ = string(name_node.GetValue());

    XmlNode description_node = root_node.GetChild(XMLNAME_INFOBASE_DESCRIPTION);
    // Description is optional
    if (description_node)
        info->description_ = string(description_node.GetValue());

    return info->version_.Load(root_node.GetChild(XMLNAME_INFOBASE_VERSION));

}

bool VersionInfo::Save(VersionInfo& info, XmlNode root_node) {

    XmlNode name_node = root_node.AddChild(XMLNAME_INFOBASE_NAME);
    name_node.SetValue(info.name_);

    XmlNode description_node = root_node.AddChild(XMLNAME_INFOBASE_DESCRIPTION);
    description_node.SetValue(info.description_.c_str());

    XmlNode version_node = root_node.AddChild();
    return info.version_.Save(version_node);

}

const string& VersionInfo::GetName() const { return name_; }
void VersionInfo::SetName(const string &name) { this->name_ = name; }

const string& VersionInfo::GetDescription() const { return description_; }
void VersionInfo::SetDescription(const string &description) { this->description_ = description; }

const Version& VersionInfo::GetVersion() const { return this->version_; }
void VersionInfo::SetVersion(const Version &version) { this->version_ = version; }

bool VersionInfo::Load(XmlNode root_node) { return VersionInfo::Load(this, root_node); }
bool VersionInfo::Save(XmlNode root_node) { return VersionInfo::Save(*this, root_node); }