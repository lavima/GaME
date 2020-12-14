/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {
    class Engine;
}

namespace game::framework {

    class System;

    class GAME_API Game {

    private:

        Engine* engine_;


        GameStatus status_;

        std::unique_ptr<GameSpecification> specification_;

        std::unique_ptr<scripting::Script> game_script_;

        std::unordered_map<std::string, std::unique_ptr<Entity>> entities_;


        Game();
        Game(GameSpecification* specification);

    public:

        virtual ~Game();

        static Game* Create();
        static Game* Create(const std::string& specification_filename);
        static Game* Create(GameSpecification* specification);

        bool Initialize(Engine& engine);

        bool Start();
        void Stop();

        bool LoadGlobalContent();
        void UnloadContent();

        void Update(GameTime& gameTime);

        std::optional<std::reference_wrapper<System>> GetSystemByName(const std::string& name);
        std::optional<std::reference_wrapper<System>> GetSystemByType(const std::string& type_name);

        std::optional<const std::vector<std::reference_wrapper<Component>>> GetComponentsByName(const std::string& name);
        std::optional<const std::vector<std::reference_wrapper<Component>>> GetComponentsByType(const std::string& type_name);

        Engine& GetEngine();
        GameStatus GetStatus();
        const GameHeader& GetHeader();
        GameConfig& GetConfig();
        GameSpecification& GetSpecification();

        const std::vector<std::reference_wrapper<Entity>> GetEntities() const;

    };

}
