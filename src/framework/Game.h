/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace pugi;

class Game {

private:

    Engine *engine;

    GameInfo *info;
    GameConfig *config;

    Script *gameScript;

    Game() {}

public:

    static Game *Load(const string &filename);

    void Initialize(Engine &engine);

    void LoadContent();
    void UnloadContent();

    void Update(GameTime &gameTime);

    const GameInfo &GetInfo();
    GameConfig &GetConfig();

};
