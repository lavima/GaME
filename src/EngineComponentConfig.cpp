/*
File: EngineComponentConfig.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

unordered_map<string, LoadEngineComponentConfigFun> EngineComponentConfig::config_loaders_;
unordered_map<string, SaveEngineComponentConfigFun> EngineComponentConfig::config_savers_;

EngineComponentConfig::EngineComponentConfig(const string &name, const string &typeName) {

    this->name_ = name;
    this->type_name_ = typeName;

}

EngineComponentConfig *EngineComponentConfig::Create(XmlNode root_node) {

    if (root_node.GetName().compare(XMLNAME_ENGINECOMPONENTCONFIG))
        return nullptr;

    XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME);
    if (!type_attribute)
        return nullptr;
    
    string type = type_attribute.GetValue();
    LoadEngineComponentConfigFun loadConfig = config_loaders_[type];
    return loadConfig(type, root_node);

}

void EngineComponentConfig::RegisterProvider(const string &typeName, LoadEngineComponentConfigFun loadFun, SaveEngineComponentConfigFun saveFun) {

   config_loaders_[typeName] = loadFun; 
   config_savers_[typeName] = saveFun; 
    
}

const string &EngineComponentConfig::GetName() const { return name_; }
const string &EngineComponentConfig::GetTypeName() const { return type_name_; }

bool EngineComponentConfig::Load(XmlNode root_node) { 

    if (root_node.GetName().compare(XMLNAME_ENGINECOMPONENTCONFIG))
        return false;

    XmlAttribute name_attribute = root_node.GetAttribute(XMLNAME_ENGINECOMPONENTCONFIG_NAME);
    if (!name_attribute)
        return false;
    name_ = name_attribute.GetValue();

    XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME);
    if (!type_attribute)
        return false;
    type_name_ = type_attribute.GetValue();

    return true;

}

bool EngineComponentConfig::Save(XmlNode root_node) { 

    root_node.SetName(XMLNAME_ENGINECOMPONENTCONFIG);

    XmlAttribute name_attribute = root_node.AddAttribute(XMLNAME_ENGINECOMPONENTCONFIG_NAME);
    name_attribute.SetValue(name_.c_str());

    XmlAttribute type_attribute = root_node.AddAttribute(XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME);
    type_attribute.SetValue(type_name_.c_str());

    return true;

}
