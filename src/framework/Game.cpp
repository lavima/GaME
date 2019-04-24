/*
File: Game.cpp
Author: Lars Vidar Magnusson
 */

#include "../GaME.h"

using namespace pugi;

void Game::Initialize(Engine &engine) {

    this->engine = &engine;

    for (unordered_map<string, string>::iterator iter = config->GetEngineComponents().begin(); iter!=config->GetEngineComponents().end(); ++iter)
        engine.AddComponent((*iter).first, (*iter).second);

}

void Game::LoadContent() {

}

void Game::UnloadContent() {

}

void Game::Update(GameTime &gameTime) {

}

const GameInfo &Game::GetInfo() { return *info; }
GameConfig &Game::GetConfig() { return *config; }

bool Game::Load(pugi::xml_node rootNode) {

    if (string(rootNode.name()).compare(XMLNAME_GAME))
        return false;

    xml_node infoNode = rootNode.child(XMLNAME_GAME_INFO);
    this->info = unique_ptr<GameInfo>(new GameInfo());
    if (!this->info->Load(infoNode))
        return false;

    xml_node configNode = rootNode.child(XMLNAME_GAME_CONFIG);
    this->config = unique_ptr<GameConfig>(new GameConfig());
    if (!this->config->Load(configNode))
        return false;

    return true;

}

bool Game::Save(pugi::xml_node rootNode) {

    rootNode.set_name(XMLNAME_GAME);

    if (!info->Save(rootNode.append_child()))
        return false;

    if (!config->Save(rootNode.append_child()))
        return false;

    return true;
}

Game::__Factory Game::__Factory::singleton;

Game::__Factory::__Factory() { Data::RegisterType(EXTENSION_GAME, &singleton); }

Data *Game::__Factory::Load(const string &filename) {                                                                                                   

    Game *newGame = new Game(filename);                                                                                                       

    if (!newGame->Load())                                                                                                                                     
        return nullptr;                                                                                                                                         

    return newGame;

}
