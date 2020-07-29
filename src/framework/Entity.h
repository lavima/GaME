/*
File: Entity.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    class Game;

    class GAME_API Entity {
    private:

        Game* game_;

        unique_ptr<EntitySpecification> specification_;

        unordered_map<string, unique_ptr<Component>> components_;

        Entity(const string& name, const string& description);

    protected:

        EntitySpecification& GetSpecification();

    public:

        static Entity* Create(const string& name, const string& description = "");
        static Entity* Create(EntitySpecification* specification);
        static Entity* Create(const Entity& parent);

        bool Initialize();
        void Update(GameTime& gameTime);
        void Destroy();


        const string& GetName() const;
        const string& GetDescription() const;

    };

}