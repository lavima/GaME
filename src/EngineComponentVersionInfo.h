/*
File: EngineComponentVersionInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_ENGINECOMPONENTINFO string("EngineComponent")

class EngineComponentVersionInfo : public VersionInfo {
public:

    EngineComponentVersionInfo(const string &name, const string &description, const Version &version);
    EngineComponentVersionInfo(XmlNode root_node);
    
};
