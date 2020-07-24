/*
File: SystemVersionInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

namespace game {

    SystemVersionInfo::SystemVersionInfo(const string& name, const string& description, const Version& version)
        : VersionInfo(name, description, version) {}

    SystemVersionInfo::SystemVersionInfo(data::xml::XmlNode root_node) : VersionInfo(root_node, XMLNAME_SYSTEMVERSIONINFO) {}

}