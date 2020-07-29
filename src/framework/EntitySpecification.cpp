#include "../GaME.h"

namespace game::framework {
    
    EntitySpecification::EntitySpecification(const string& name, const string& description) 
        : XmlData(name + "." + EXTENSION_ENTITY) {
        name_ = name;
        description_ = description;
    }
    
    EntitySpecification::EntitySpecification(const string& filename) : XmlData(filename) {}
    
    EntitySpecification* EntitySpecification::Create(const string& name, const string& description) {
        return new EntitySpecification(name, description);
    }

    EntitySpecification* EntitySpecification::Create(const string& filename) {

        auto spec = new EntitySpecification(filename);
        
        if (!spec->Load())
            return nullptr;

        return spec;

    }

    bool EntitySpecification::Load(data::xml::XmlNode root_node) {
        
        if (root_node.GetName().compare(XMLNAME_ENTITY))
            return false;

        data::xml::XmlNode name_node = root_node.GetChild(XMLNAME_ENTITY_NAME);
        if (!name_node)
            return false;
        name_ = string(name_node.GetValue());

        data::xml::XmlNode description_node = root_node.GetChild(XMLNAME_ENTITY_DESCRIPTION);
        // Description is optional
        if (description_node)
            description_ = string(description_node.GetValue());

        for (data::xml::XmlNode component_node : root_node.GetChildren(XMLNAME_ENTITY_COMPONENT)) {

            ComponentConfig* component_config = ComponentConfig::Create(component_node);
            if (!component_config)
                return false;

            components_.push_back(unique_ptr<ComponentConfig>(component_config));

        }

        return true;

    }

    bool EntitySpecification::Save(data::xml::XmlNode root_node) {
        
        data::xml::XmlNode name_node = root_node.AddChild(XMLNAME_ENTITY_NAME);
        name_node.SetValue(name_);

        data::xml::XmlNode description_node = root_node.AddChild(XMLNAME_ENTITY_DESCRIPTION);
        description_node.SetValue(description_);

        return true;
    }

    const string& EntitySpecification::GetName() const {
        return name_;
    }

    const string& EntitySpecification::GetDescription() const {
        return description_;
    }

    data::Data* EntitySpecification::Loader::Load(const string& filename) {

        EntitySpecification* entity = new EntitySpecification(filename);

        if (!entity->Load())
            return nullptr;

        return entity;

    }
}