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
    
    static bool Load(EngineComponentVersionInfo *info, XmlNode root_node);
    static bool Save(EngineComponentVersionInfo &info, XmlNode root_node);

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;
    
};
