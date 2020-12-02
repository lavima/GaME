/*
File: Entity.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    class Game;

    enum class EntityStatus : uint32_t {
        Created = 0,
        Initialized = 1,
        Spawned = 2,
        Killed = 3,
        Destroyed = 4
    };

    class GAME_API Entity {
    private:

        Game* game_;

        EntityStatus status_;

        std::unique_ptr<EntitySpecification> specification_;

        std::unordered_map<std::string, std::unique_ptr<Component>> components_;

        Entity(Game& game, const std::string& name, const std::string& description);
        Entity(Game& game, EntitySpecification* specification);

    protected:

        

    public:

        static Entity* Create(Game& game, const std::string& name, const std::string& description = "");
        static Entity* Create(Game& game, EntitySpecification* specification);
        static Entity* Create(Game& game, const Entity& parent);

        void AddComponent(Component* component);

        bool Initialize();
        bool Spawn(const GameTime& game_time);
        void Update(const GameTime& gameTime);
        void Kill();
        void Destroy();

        Game& GetGame() const;
        EntitySpecification& GetSpecification();
        EntityStatus GetStatus() const;
        const std::string& GetName() const;
        const std::string& GetDescription() const;
        const std::vector<std::reference_wrapper<Component>> GetComponents() const;

    };

}