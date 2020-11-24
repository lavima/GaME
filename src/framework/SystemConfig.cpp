/*
File: SystemConfig.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

namespace game {

    unordered_map<string, SystemConfig::ILoader*>* SystemConfig::loaders_ = nullptr;

    SystemConfig::SystemConfig(const string& name, const string& typeName) {

        this->name_ = name;
        this->type_name_ = typeName;

    }

    SystemConfig::SystemConfig(data::xml::XmlNode root_node) {
        assert(this->Load(root_node));
    }

    SystemConfig* SystemConfig::Create(data::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_SYSTEMCONFIG))
            return nullptr;

        data::xml::XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        if (!type_attribute)
            return nullptr;

        string type = type_attribute.GetValue();

        return (*loaders_)[type]->Load(root_node);

    }

    void SystemConfig::RegisterType(const string& typeName, ILoader* loader) {

        if (!loaders_)
            loaders_ = new unordered_map<string, ILoader*>();

        loaders_->insert_or_assign(typeName, loader);

    }

    const string& SystemConfig::GetName() const { return name_; }
    const string& SystemConfig::GetTypeName() const { return type_name_; }

    bool SystemConfig::Load(data::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_SYSTEMCONFIG))
            return false;

        data::xml::XmlAttribute name_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_NAME);
        if (!name_attribute)
            return false;
        name_ = name_attribute.GetValue();

        data::xml::XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        if (!type_attribute)
            return false;
        type_name_ = type_attribute.GetValue();

        return true;

    }

    bool SystemConfig::Save(data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_SYSTEMCONFIG);

        data::xml::XmlAttribute name_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_NAME);
        name_attribute.SetValue(name_.c_str());

        data::xml::XmlAttribute type_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        type_attribute.SetValue(type_name_.c_str());

        return true;

    }

}