/*
File: Game.cpp
Author: Lars Vidar Magnusson
 */

#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include <optional>

#include <pugixml.hpp>
#include <v8.h>

#include "../global.h"
#include "../lib/string_util.h"
#include "../lib/file_path.h"
#include "../log.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "../scripting/script_environment.h"
#include "../scripting/script.h"
#include "../scripting/scriptable.h"
#include "../platform/input_key.h"
#include "../platform/platform_config.h"
#include "../platform/platform.h"
#include "framework.h"
#include "component_info.h"
#include "component_config.h"
#include "system_info.h"
#include "system_config.h"
#include "game_time.h"
#include "component.h"
#include "entity_specification.h"
#include "entity.h"
#include "game_config.h"
#include "game_header.h"
#include "game_specification.h"
#include "game.h"
#include "system.h"
#include "../addin/system_provider.h"
#include "../addin/addin_header.h"
#include "../addin/addin.h"
#include "../engine_config.h"
#include "../engine.h"

namespace game::framework {

    Game::Game(GameSpecification* specification) {

        specification_ = std::unique_ptr<GameSpecification>(specification);
        status_ = GameStatus::Created;

    }


    Game* Game::Create() {
        return Create(GameSpecification::Create());
    }

    Game* Game::Create(GameSpecification* specification) {
        return new Game(specification);
    }

    Game* Game::Create(const std::string& specification_filename) {
        
        GameSpecification* specification = content::Content::Load<GameSpecification>(specification_filename);
        if (!specification)
            return nullptr;

        return Create(specification);

    }

    bool Game::Initialize(Engine& engine) {

        engine_ = &engine;

        for (const SystemInfo& system_info:GetHeader().GetRequiredSystems()) {
            if (!System::IsTypeAvailable(system_info.GetName())) {
                LOG_ERROR("The engine does not support the system type %s", system_info.GetName());
                return false;
            }
        }

        for (SystemConfig& system_config:GetConfig().GetSystemConfigs()) {
            if (!engine_->LoadSystem(system_config)) {
                LOG_ERROR("Couldn't load system %s", system_config.GetName());
                return false;
            }
        }

        status_ = GameStatus::Initialized;

        return true;
    }

    bool Game::Start() {
        Log& log = engine_->GetLog();

        if (status_!=GameStatus::Initialized)
            return false;

        for (EntitySpecification& entity_spec:specification_->GetEntities()) {
            LOG_INFO("Creating entity %s", entity_spec.GetName());
            Entity* entity = Entity::Create(*this, &entity_spec);
            if (!entity) {
                LOG_ERROR("Failed to create entity %s", entity_spec.GetName());
                return false;
            }
            entities_.insert_or_assign(entity->GetName(), std::unique_ptr<Entity>(entity));
        }

        for (auto& entity_pair:entities_) {
            Entity& entity = *entity_pair.second;
            LOG_INFO("Initializing entity %s", entity.GetName());
            if (!entity.Initialize()) {
                LOG_ERROR("Failed to initialize entity %s", entity.GetName());
                return false;
            }
        }

        status_ = GameStatus::Running;

        return true;
    }

    void Game::Stop() {
        if (status_!=GameStatus::Running)
            return;
        status_ = GameStatus::Terminated;
    }

    bool Game::LoadGlobalContent() {
        return true;
    }

    void Game::UnloadContent() {

    }

    void Game::Update(GameTime& game_time) {
        for (auto& entity_pair:entities_) {
            (*entity_pair.second).Update(game_time);
        }
    }

    std::optional<std::reference_wrapper<System>> Game::GetSystemByName(const std::string& name) {
        return engine_->GetSystemByName(name);
    }

    std::optional<std::reference_wrapper<System>> Game::GetSystemByType(const std::string& type_name) {
        return engine_->GetSystemByType(type_name);
    }

    std::optional<const std::vector<std::reference_wrapper<Component>>> Game::GetComponentsByName(const std::string& name) {
        return engine_->GetComponentsByName(name);
    }

    std::optional<const std::vector<std::reference_wrapper<Component>>> Game::GetComponentsByType(const std::string& type_name) {
        return engine_->GetComponentsByType(type_name);
    }

    Engine& Game::GetEngine() {
        return *engine_;
    }

    GameStatus Game::GetStatus() {
        return status_;
    }

    const GameHeader& Game::GetHeader() { return *specification_->header_; }
    GameConfig& Game::GetConfig() { return *specification_->config_; }

    GameSpecification& Game::GetSpecification() { return *specification_; }

    const std::vector<std::reference_wrapper<Entity>> Game::GetEntities() const {
        std::vector<std::reference_wrapper<Entity>> entities;
        entities.reserve(entities_.size());
        transform(entities_.begin(), entities_.end(), back_inserter(entities),
            [&](auto& entity_pair) { return std::reference_wrapper<Entity>(*entity_pair.second); });
        return entities;
    }

}
