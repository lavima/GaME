/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

AddinType AddinInfo::GetType() { return this->type; }
const string &AddinInfo::GetLibraryFilename() { return this->libraryFilename; }

const vector<reference_wrapper<const EngineComponentInfo>> AddinInfo::GetEngineComponents() const { 
    return vector<reference_wrapper<const EngineComponentInfo>>(engineComponents.begin(), engineComponents.end()); 
}

bool AddinInfo::Load(xml_node rootNode) {

    if (string(rootNode.value()).compare(XMLNAME_ADDIN))
        return false;

    xml_attribute libraryAttribute = rootNode.attribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
    if (!libraryAttribute)
        return false;
    this->libraryFilename = string(libraryAttribute.value());

    xml_node componentNode = rootNode.child(XMLNAME_ADDININFO_ENGINECOMPONENT);
    if (componentNode)
        this->type = ENGINE_COMPONENT_ADDIN;
    else
        return false;

    for (; componentNode; componentNode = componentNode.next_sibling(XMLNAME_ADDININFO_ENGINECOMPONENT)) {
        engineComponents.push_back(EngineComponentInfo(componentNode));
    }

    return true;

}

bool AddinInfo::Save(xml_node rootNode) {

    rootNode.set_name(XMLNAME_ADDIN);

    xml_attribute libraryAttribute = rootNode.append_attribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
    libraryAttribute.set_value(libraryFilename.c_str());

    for (EngineComponentInfo &componentInfo : engineComponents) 
        componentInfo.Save(rootNode.append_child()); 

    return true;

}

AddinInfo::__Factory AddinInfo::__Factory::singleton;

AddinInfo::__Factory::__Factory() { Data::RegisterType(EXTENSION_ADDIN, &singleton); }

Data *AddinInfo::__Factory::Load(const string &filename) { 

    AddinInfo *newAddinInfo = new EngineConfig(filename);

    if (!newAddinInfo->Load())
        return nullptr;

    return newAddinInfo;

}
