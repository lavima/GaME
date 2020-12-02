#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>

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
#include "game_time.h"
#include "component.h"
#include "entity_specification.h"
#include "entity.h"

namespace game::framework {


    std::unordered_map<std::string, Component::ICreator*>* Component::creators_ = nullptr;

    Component::Component(Entity& entity, const std::string& name, const std::string& type_name) {
        entity_ = &entity;
        config_ = ComponentConfig::Create(name, type_name);
        entity.GetSpecification().AddComponent(config_);
        status_ = ComponentStatus::Created;
    }

    Component::Component(Entity& entity, ComponentConfig& config, bool store_config_in_entity) {
        entity_ = &entity;
        config_ = &config;
        if (store_config_in_entity)
            entity.GetSpecification().AddComponent(config_);
        status_ = ComponentStatus::Created;
    }

    void Component::RegisterType(const std::string& type_name, Component::ICreator *creator) {
        if (!creators_)
            creators_ = new std::unordered_map<std::string, ICreator*>();
        creators_->insert_or_assign(type_name, creator);
    }

    Component* Component::Create(Entity& entity, const std::string& name, const std::string& type_name) {
        auto config = ComponentConfig::Create(name, type_name);
        return Create(entity, *config);
    }

    Component* Component::Create(Entity& entity, ComponentConfig& config) {
        assert(creators_);
        if (creators_->find(config.GetTypeName())==creators_->end())
            return nullptr;
        return (*creators_)[config.GetTypeName()]->Create(entity, config);
    }

    bool Component::Initialize() {
        status_ = ComponentStatus::Initialized;
        return true;
    }

    void Component::Destroy() {
        status_ = ComponentStatus::Destroyed;
    }

    Entity& Component::GetEntity() const {
        return *entity_;
    }

    ComponentStatus Component::GetStatus() const {
        return status_;
    }

    ComponentConfig& Component::GetConfig() {
        return *config_;
    }

}
