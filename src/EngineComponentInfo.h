/*
File: EngineComponentInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_ENGINECOMPONENTINFO "EngineComponent"

class EngineComponentInfo : public __InfoBase, public XMLSerializable {
public:
    EngineComponentInfo(const string &name, const string &description, const Version &version);
    EngineComponentInfo(pugi::xml_node rootNode);
    
    static bool Load(EngineComponentInfo *info, pugi::xml_node rootNode);
    static bool Load(EngineComponentInfo &info, pugi::xml_node rootNode);

    bool Load(pugi::xml_node rootNode);
    bool Save(pugi::xml_node rootNode);
    
};
