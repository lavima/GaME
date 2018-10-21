/*
File: Game.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

Game *Game::Load(const string &filename) {

    Game *newGame = new Game();
    newGame->info = GameInfo::Load(filename);

    return newGame;

}

void Game::Initialize(Engine &engine) {

    this->engine = &engine;
    
    for (EngineComponentNameConstIter iter = info->GetEngineComponents().begin(); iter!=info->GetEngineComponents().end(); ++iter)
        engine.AddComponent((*iter).first, *(*iter).second);

}

void Game::LoadContent() {

}

void Game::UnloadContent() {

}

void Game::Update(GameTime &gameTime) {

}

const GameInfo &Game::GetInfo() { return *info; }

