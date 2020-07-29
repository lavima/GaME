#include "../GaME.h"

namespace game::framework {

    unordered_map<string, ComponentConfig::ICreator*>* ComponentConfig::creators_ = nullptr;

    ComponentConfig::ComponentConfig(const string& name, const string& type_name, bool shared) {
        
        name_ = name;
        type_name_ = type_name;
        shared_ = shared;

    }

    ComponentConfig::ComponentConfig(data::xml::XmlNode root_node) {
        assert(Load(root_node));
    }

    ComponentConfig* ComponentConfig::Create(const string& name, const string& type_name, bool shared) {
        return new ComponentConfig(name, type_name, shared);
    }

    ComponentConfig* ComponentConfig::Create(data::xml::XmlNode root_node) {
        return new ComponentConfig(root_node);
    }

    void ComponentConfig::RegisterType(const string& type_name, ICreator* creator) {
        
        if (!creators_)
            creators_ = new unordered_map<string, ICreator*>();

        creators_->insert_or_assign(type_name, creator);

    }

    const string& ComponentConfig::GetName() const {
        return name_;
    }

    const string& ComponentConfig::GetTypeName() const {
        return type_name_;
    }

    const bool ComponentConfig::IsShared() const {
        return shared_;
    }

    bool ComponentConfig::Load(data::xml::XmlNode root_node) {
        
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

    bool ComponentConfig::Save(data::xml::XmlNode root_node) {
        
        root_node.SetName(XMLNAME_SYSTEMCONFIG);

        data::xml::XmlAttribute name_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_NAME);
        name_attribute.SetValue(name_.c_str());

        data::xml::XmlAttribute type_attribute = root_node.AddAttribute(XMLNAME_SYSTEMCONFIG_TYPENAME);
        type_attribute.SetValue(type_name_.c_str());

        return true;

    }

}