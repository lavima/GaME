/*
File: EngineComponentInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

EngineComponentInfo::EngineComponentInfo(const string &name, const string &description, const Version &version) 
    : __InfoBase(name, description, version) {}

EngineComponentInfo::EngineComponentInfo(xml_node rootNode) {
    assert(EngineComponentInfo::Load(this, rootNode));
}

bool EngineComponentInfo::Load(EngineComponentInfo *info, xml_node rootNode) {

    if (string(rootNode.value()).compare(XMLNAME_ENGINECOMPONENTINFO))
        return false;

    return ((__InfoBase *)info)->Load(rootNode);

}

bool EngineComponentInfo::Save(EngineComponentInfo &info, xml_node rootNode) {

    rootNode.set_name(XMLNAME_ENGINECOMPONENTINFO);

    return ((__InfoBase &)info).Save(rootNode);

}

bool EngineComponentInfo::Load(pugi::xml_node rootNode) { return EngineComponentInfo::Load(this, rootNode); }
bool EngineComponentInfo::Save(pugi::xml_node rootNode) { return EngineComponentInfo::Save(*this, rootNode); }


