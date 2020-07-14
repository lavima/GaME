/*
File: EngineComponentVersionInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

EngineComponentVersionInfo::EngineComponentVersionInfo(const string &name, const string &description, const Version &version)
    : VersionInfo(name, description, version) {}

EngineComponentVersionInfo::EngineComponentVersionInfo(XmlNode root_node) : VersionInfo(root_node, XMLNAME_ENGINECOMPONENTINFO) {}
