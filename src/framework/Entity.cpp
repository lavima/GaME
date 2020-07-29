/*
File: Entity.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h" 

namespace game::framework {

    Entity::Entity(const string& name, const string& description) {
        specification_ = unique_ptr<EntitySpecification>(new EntitySpecification(name, description));
    }

    EntitySpecification& Entity::GetSpecification() {
        return *specification_;
    }

    Entity* Entity::Create(const string& name, const string& description) {
        
        Entity* entity = new Entity(name, description);

        return entity;

    }

    Entity* Entity::Create(EntitySpecification* specification) {
        return nullptr;
    }

    Entity* Entity::Create(const Entity& parent) {
        return nullptr;
    }

    bool Entity::Initialize() {
        return true;
    }

    void Entity::Update(GameTime& gameTime) {

    }

    void Entity::Destroy() {
    
    }

    const string& Entity::GetName() const {
        return specification_->GetName();
    }

    const string& Entity::GetDescription() const {
        return specification_->GetDescription();
    }

}