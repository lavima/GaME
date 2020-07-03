/*
File: EngineComponentVersionInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

EngineComponentVersionInfo::EngineComponentVersionInfo(const string &name, const string &description, const Version &version)
    : VersionInfo(name, description, version) {}

EngineComponentVersionInfo::EngineComponentVersionInfo(XmlNode root_node) {
    assert(EngineComponentVersionInfo::Load(this, root_node));
}

bool EngineComponentVersionInfo::Load(EngineComponentVersionInfo* info, XmlNode root_node) {

    if (root_node.GetValue().compare(XMLNAME_ENGINECOMPONENTINFO))
        return false;

    return ((VersionInfo*)info)->Load(root_node);

}

bool EngineComponentVersionInfo::Save(EngineComponentVersionInfo& info, XmlNode root_node) {

    root_node.SetName(XMLNAME_ENGINECOMPONENTINFO);

    return ((VersionInfo&)info).Save(root_node);

}

bool EngineComponentVersionInfo::Load(XmlNode root_node) { return EngineComponentVersionInfo::Load(this, root_node); }
bool EngineComponentVersionInfo::Save(XmlNode root_node) { return EngineComponentVersionInfo::Save(*this, root_node); }


