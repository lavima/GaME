#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../lib/file_path.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "framework.h"
#include "component_config.h"

namespace game::framework {

    std::unordered_map<std::string, ComponentConfig::ICreator*>* ComponentConfig::creators_ = nullptr;

    ComponentConfig::ComponentConfig(const std::string& name, const std::string& type_name, bool shared) {
        
        name_ = name;
        type_name_ = type_name;
        shared_between_entities_ = shared;

    }

    ComponentConfig::ComponentConfig(content::xml::XmlNode root_node) {
        assert(Load(root_node));
    }

    ComponentConfig::~ComponentConfig() {}

    ComponentConfig* ComponentConfig::Create(const std::string& name, const std::string& type_name, bool shared) {
        return new ComponentConfig(name, type_name, shared);
    }

    ComponentConfig* ComponentConfig::Create(content::xml::XmlNode root_node) {
        return new ComponentConfig(root_node);
    }

    void ComponentConfig::RegisterType(const std::string& type_name, ICreator* creator) {
        
        if (!creators_)
            creators_ = new std::unordered_map<std::string, ICreator*>();

        creators_->insert_or_assign(type_name, creator);

    }

    const std::string& ComponentConfig::GetName() const {
        return name_;
    }

    const std::string& ComponentConfig::GetTypeName() const {
        return type_name_;
    }

    bool ComponentConfig::IsShared() const {
        return shared_between_entities_;
    }

    bool ComponentConfig::Load(content::xml::XmlNode root_node) {
        
        if (root_node.GetName().compare(XMLNAME_COMPONENTCONFIG))
            return false;

        content::xml::XmlAttribute name_attribute = root_node.GetAttribute(XMLNAME_COMPONENTCONFIG_NAME);
        if (!name_attribute)
            return false;
        name_ = name_attribute.GetValue();

        content::xml::XmlAttribute type_attribute = root_node.GetAttribute(XMLNAME_COMPONENTCONFIG_TYPENAME);
        if (!type_attribute)
            return false;
        type_name_ = type_attribute.GetValue();

        return true;

    }

    bool ComponentConfig::Save(content::xml::XmlNode root_node) {
        
        root_node.SetName(XMLNAME_COMPONENTCONFIG);

        content::xml::XmlAttribute name_attribute = root_node.AddAttribute(XMLNAME_COMPONENTCONFIG_NAME);
        name_attribute.SetValue(name_.c_str());

        content::xml::XmlAttribute type_attribute = root_node.AddAttribute(XMLNAME_COMPONENTCONFIG_TYPENAME);
        type_attribute.SetValue(type_name_.c_str());

        return true;

    }

}
