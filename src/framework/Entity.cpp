/*
File: Entity.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>

#include <pugixml.hpp>

#include "../global.h"
#include "../lib/string_util.h"
#include "../Log.h"
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

    Entity::Entity(Game& game, const std::string& name, const std::string& description)
        : Entity(game, new EntitySpecification(name, description)) {}

    Entity::Entity(Game& game, EntitySpecification* specification) {
     
        game_ = &game;
        specification_ = std::unique_ptr<EntitySpecification>(specification);

        status_ = EntityStatus::Created;
    }

    Entity* Entity::Create(Game& game, const std::string& name, const std::string& description) {
        
        Entity* entity = new Entity(game, name, description);
        return entity;
    }

    Entity* Entity::Create(Game& game, EntitySpecification* specification) {
        return new Entity(game, specification);
    }

    Entity* Entity::Create(Game& game, const Entity& parent) {
        return nullptr;
    }

    void Entity::AddComponent(Component* component) {
        
        if (components_.find(component->GetConfig().GetName())!=components_.end())
            return;

        components_[component->GetConfig().GetName()] = std::unique_ptr<Component>(component);

        if (status_>=EntityStatus::Initialized && component->GetStatus()<ComponentStatus::Initialized)
            component->Initialize();

    }

    bool Entity::Initialize() {

        for (auto& component_config:specification_->GetComponents()) {
            LOG_INFO("Creating component %s", component_config.get().GetName().c_str());
            Component* component = Component::Create(*this, component_config);
            if (!component) {
                LOG_ERROR("Failed to create component %s", component_config.get().GetName().c_str());
                return false;
            }
            AddComponent(component);
        }

        for (auto& component_pair:components_) {
            LOG_INFO("Initializing component %s", component_pair.second->GetConfig().GetName().c_str());
            if (!component_pair.second->Initialize()) {
                LOG_ERROR("Failed to initialize component %s", component_pair.second->GetConfig().GetName().c_str());
                return false;
            }
        }

        status_ = EntityStatus::Initialized;

        return true;
    }

    bool Entity::Spawn(const GameTime& game_time) {
    
        if (status_!=EntityStatus::Initialized)
            return false;

    }

    void Entity::Update(const GameTime& game_time) {
        for (auto& component_pair:components_)
            component_pair.second->Update(game_time);
    }

    void Entity::Kill() {}

    void Entity::Destroy() {
    
    }

    Game& Entity::GetGame() const {
        return *game_;
    }

    EntitySpecification& Entity::GetSpecification() {
        return *specification_;
    }

    EntityStatus Entity::GetStatus() const {
        return status_;
    }

    const std::string& Entity::GetName() const {
        return specification_->GetName();
    }

    const std::string& Entity::GetDescription() const {
        return specification_->GetDescription();
    }

    const std::vector<std::reference_wrapper<Component>> Entity::GetComponents() const {
        std::vector<std::reference_wrapper<Component>> components;
        components.reserve(components_.size());
        transform(components_.begin(), components_.end(), back_inserter(components),
            [&](auto& component_pair) { return std::reference_wrapper<Component>(*component_pair.second); });
        return components;
    }

}
