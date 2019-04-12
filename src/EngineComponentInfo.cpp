/*
File: EngineComponentInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

EngineComponentInfo::EngineComponentInfo(const string &name, const string &description, const Version &version);
EngineComponentInfo::EngineComponentInfo(pugi::xml_node rootNode);

static bool EngineComponentInfo::Load(EngineComponentInfo *info, pugi::xml_node rootNode) {

    if (string(rootNode.value()).compare(XMLNAME_ENGINECOMPONENTINFO))
        return false;

    return ((__InfoBase *)info)->Load(rootNode);

}

static bool EngineComponentInfo::Load(EngineComponentInfo &info, pugi::xml_node rootNode) {

    rootNode.set_name(XMLNAME_ENGINECOMPONENTINFO);

    return ((__InfoBase &)info).Save(rootNode);

}

bool EngineComponentInfo::Load(pugi::xml_node rootNode) { return Load(this, rootNode); }
bool EngineComponentInfo::Save(pugi::xml_node rootNode) { return Save(*this, rootNode); }


