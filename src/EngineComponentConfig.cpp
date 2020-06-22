/*
File: EngineComponentConfig.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

EngineComponentConfig::EngineComponentConfig(const string &name, const string &typeName) {

    this->name = name;
    this->typeName = typeName;

}

EngineComponentConfig *EngineComponentConfig::Create(pugi::xml_node rootNode) {

    if (string(rootNode.name()).compare(XMLNAME_ENGINECOMPONENTCONFIG))
        return nullptr;

    xml_attribute typeNameAttribute = rootNode.attribute(XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME);
    if (!typeNameAttribute)
        return nullptr;
    string typeName = string(typeNameAttribute.value());

    LoadEngineComponentConfig loadConfig = configLoaders[typeName];
    return loadConfig(typeName, rootNode);

}

void EngineComponentConfig::RegisterProvider(const string &typeName, LoadEngineComponentConfig loadFun, SaveEngineComponentConfig saveFun) { 

   configLoaders[typeName] = loadFun; 
   configSavers[typeName] = saveFun; 
    
}

const string &EngineComponentConfig::GetName() const { return name; }
const string &EngineComponentConfig::GetTypeName() const { return typeName; }

bool EngineComponentConfig::Load(xml_node rootNode) { 

    if (string(rootNode.name()).compare(XMLNAME_ENGINECOMPONENTCONFIG))
        return false;

    xml_attribute nameAttribute = rootNode.attribute(XMLNAME_ENGINECOMPONENTCONFIG_NAME);
    if (!nameAttribute)
        return false;
    name = string(nameAttribute.value());

    xml_attribute typeNameAttribute = rootNode.attribute(XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME);
    if (!typeNameAttribute)
        return false;
    typeName = string(typeNameAttribute.value());

    return true;

}

bool EngineComponentConfig::Save(xml_node rootNode) { 

    rootNode.set_name(XMLNAME_ENGINECOMPONENTINSTANCE);

    xml_attribute nameAttribute = rootNode.append_attribute(XMLNAME_ENGINECOMPONENTINSTANCE_NAME);
    nameAttribute.set_value(name.c_str());

    xml_attribute typeNameAttribute = rootNode.append_attribute(XMLNAME_ENGINECOMPONENTINSTANCE_TYPENAME);
    nameAttribute.set_value(typeName.c_str());

    return true;

}
