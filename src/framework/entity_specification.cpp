#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
#include "component_config.h"
#include "entity_specification.h"

namespace game::framework {
    
    EntitySpecification::EntitySpecification(const std::string& name, const std::string& description)
        : XmlContent(name + "." + EXTENSION_ENTITY) {
        name_ = name;
        description_ = description;
    }
    
    EntitySpecification::EntitySpecification(const std::string& filename) : XmlContent(filename) {}
    
    EntitySpecification* EntitySpecification::Create(const std::string& name, const std::string& description) {
        return new EntitySpecification(name, description);
    }

    EntitySpecification* EntitySpecification::Create(const std::string& filename) {

        auto spec = new EntitySpecification(filename);
        
        if (!spec->Load())
            return nullptr;

        return spec;

    }

    bool EntitySpecification::Load(content::xml::XmlNode root_node) {
        
        if (root_node.GetName().compare(XMLNAME_ENTITY))
            return false;

        content::xml::XmlNode name_node = root_node.GetChild(XMLNAME_ENTITY_NAME);
        if (!name_node)
            return false;
        name_ = std::string(name_node.GetValue());

        content::xml::XmlNode description_node = root_node.GetChild(XMLNAME_ENTITY_DESCRIPTION);
        // Description is optional
        if (description_node)
            description_ = std::string(description_node.GetValue());

        for (content::xml::XmlNode component_node : root_node.GetChildren(XMLNAME_ENTITY_COMPONENT)) {

            ComponentConfig* component_config = ComponentConfig::Create(component_node);
            if (!component_config)
                return false;

            components_.push_back(std::unique_ptr<ComponentConfig>(component_config));

        }

        return true;

    }

    bool EntitySpecification::Save(content::xml::XmlNode root_node) {
        
        content::xml::XmlNode name_node = root_node.AddChild(XMLNAME_ENTITY_NAME);
        name_node.SetValue(name_);

        content::xml::XmlNode description_node = root_node.AddChild(XMLNAME_ENTITY_DESCRIPTION);
        description_node.SetValue(description_);

        return true;
    }

    const std::string& EntitySpecification::GetName() const {
        return name_;
    }

    const std::string& EntitySpecification::GetDescription() const {
        return description_;
    }

    const std::vector<std::reference_wrapper<ComponentConfig>> EntitySpecification::GetComponents() {
        std::vector<std::reference_wrapper<ComponentConfig>> components;
        components.reserve(components_.size());
        transform(components_.begin(), components_.end(), back_inserter(components), 
            [&](auto& component) { return std::reference_wrapper<ComponentConfig>(*component); });
        return components;
    }

    bool EntitySpecification::AddComponent(ComponentConfig* config) {
        for (auto& component:components_)
            if (component->GetName()==config->GetName())
                return false;
        components_.push_back(std::unique_ptr<ComponentConfig>(config));
        return true;
    }

    EntitySpecification::Loader EntitySpecification::Loader::singleton_;

    EntitySpecification::Loader::Loader() { Content::RegisterType(EXTENSION_ENTITY, &singleton_); }

    content::Content* EntitySpecification::Loader::Load(const std::string& filename) {

        EntitySpecification* entity = new EntitySpecification(filename);

        if (!entity->Load())
            return nullptr;

        return entity;

    }
}
