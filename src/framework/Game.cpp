/*
File: Game.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

Game *Game::Load(const string &filename) {

    xml_document *document = PugiXML::ParseDocument(filename);
    xml_node rootNode = document->document_element();

    Game *newGame = new Game();
    xml_node infoNode = rootNode.child("Info");
    newGame->info = GameInfo::Load(infoNode);
    xml_node configNode = rootNode.child("Config");
    newGame->config = GameConfig::Load(configNode);

    return newGame;

}

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

