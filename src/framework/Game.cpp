/*
File: Game.cpp
Author: Lars Vidar Magnusson
 */

#include "../GaME.h"

Game::Game(GameSpecification* specification) {

    specification_ = unique_ptr<GameSpecification>(specification); 
    status_ = GameStatus::Created;

}


bool Game::Initialize(Engine &engine) {

    engine_ = &engine;
    
    for (const EngineComponentVersionInfo& component_type:GetHeader().GetRequiredComponents()) {
        if (!engine.HasComponentType(component_type.GetName())) {
            engine.GetLog().AddEvent(EventType::Error,
                "The engine does not support the component type %s", component_type.GetName());
            return false;
        }
    }

    for(EngineComponentConfig* component_config : GetConfig().GetEngineComponentConfigs())
        engine.AddComponent(component_config->GetTypeName(), component_config->GetName());

    status_ = GameStatus::Initialized;

    return true;

}

void Game::Run() {
    

}

void Game::LoadGlobalContent() {

}

void Game::UnloadContent() {

}

void Game::Update(GameTime &gameTime) {

}

GameStatus Game::GetStatus() {
    return status_;
}

const GameHeader &Game::GetHeader() { return *specification_->header_; }
GameConfig &Game::GetConfig() { return *specification_->config_; }

GameSpecification& Game::GetSpecification() { return *specification_; }


