/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    enum class GAME_API GameStatus {
        Created = 0,
        Initialized,
        Running,
        Paused,
        Terminated
    };

    class GAME_API Game {

    private:

        GameStatus status_;

        unique_ptr<GameSpecification> specification_;

        unique_ptr<scripting::Script> game_script_;

        Engine* engine_;

    public:

        Game(GameSpecification* specification);

        bool Initialize(Engine& engine);

        bool Start();
        void Stop();

        bool LoadGlobalContent();
        void UnloadContent();

        void Update(GameTime& gameTime);

        GameStatus GetStatus();
        const GameHeader& GetHeader();
        GameConfig& GetConfig();
        GameSpecification& GetSpecification();

    };

}