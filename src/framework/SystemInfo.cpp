/*
File: SystemInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

namespace game {

    SystemInfo::SystemInfo(const string& name, const string& description, const Version& version)
        : VersionInfo(name, description, version) {}

    SystemInfo::SystemInfo(data::xml::XmlNode root_node) : VersionInfo(root_node, XMLNAME_SYSTEMVERSIONINFO) {}

}