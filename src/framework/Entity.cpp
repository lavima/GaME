/*
File: Entity.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h" 

namespace game::framework {

    Entity::Entity(const string& name) : name_(name) {}

    Entity* Entity::Create(const string& name) {
        
        Entity* entity = new Entity(name);

        return entity;

    }

    void Entity::Initialize() {

    }

    void Entity::Update(GameTime& gameTime) {

    }

}