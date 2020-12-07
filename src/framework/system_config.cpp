/*
File: SystemConfig.cpp
Author: Lars Vidar Magnusson
 */

#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "framework.h"
#include "system_config.h"

namespace game::framework {

    std::unordered_map<std::string, SystemConfig::ILoader*>* SystemConfig::loaders_ = nullptr;

    SystemConfig::SystemConfig(const std::string& name, const std::string& typeName, GameLoopStage update_stage, float time_between_updates) {

        this->name_ = name;
        this->type_name_ = typeName;

    }

    SystemConfig::SystemConfig(content::xml::XmlNode root_node) {
        assert(this->Load(root_node));
    }

    SystemConfig* SystemConfig::Create(content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_SYSTEMCONFIG))
            return nullptr;

        content::xml::XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        if (!type_attribute)
            return nullptr;

        std::string type = type_attribute.GetValue();

        return (*loaders_)[type]->Load(root_node);

    }

    void SystemConfig::RegisterType(const std::string& typeName, ILoader* loader) {

        if (!loaders_)
            loaders_ = new std::unordered_map<std::string, ILoader*>();

        loaders_->insert_or_assign(typeName, loader);

    }

    const std::string& SystemConfig::GetName() const { return name_; }
    const std::string& SystemConfig::GetTypeName() const { return type_name_; }

    bool SystemConfig::Load(content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_SYSTEMCONFIG))
            return false;

        content::xml::XmlAttribute name_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_NAME);
        if (!name_attribute)
            return false;
        name_ = name_attribute.GetValue();

        content::xml::XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        if (!type_attribute)
            return false;
        type_name_ = type_attribute.GetValue();

        return true;

    }

    bool SystemConfig::Save(content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_SYSTEMCONFIG);

        content::xml::XmlAttribute name_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_NAME);
        name_attribute.SetValue(name_.c_str());

        content::xml::XmlAttribute type_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        type_attribute.SetValue(type_name_.c_str());

        return true;

    }

}
