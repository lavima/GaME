/*
File: GameConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

namespace game::framework {

    GameConfig::GameConfig(data::xml::XmlNode root_node) { assert(GameConfig::Load(this, root_node)); }

    bool GameConfig::Load(GameConfig* config, data::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_GAMECONFIG))
            return false;

        for (data::xml::XmlNode engine_component_config_node : root_node.GetChildren(XMLNAME_GAMECONFIG_ENGINECOMPONENT)) {

            SystemConfig* component_config = SystemConfig::Create(engine_component_config_node);
            if (!component_config)
                return false;

            config->engine_component_configs_.push_back(*component_config);

        }

        return true;
    }

    bool GameConfig::Save(const GameConfig& config, data::xml::XmlNode root_node) {

        return true;
    }

    const vector<reference_wrapper<SystemConfig>> GameConfig::GetEngineComponentConfigs() {
        return vector<reference_wrapper<SystemConfig>>(engine_component_configs_.begin(), engine_component_configs_.end());
    }

    bool GameConfig::Load(data::xml::XmlNode root_node) { return GameConfig::Load(this, root_node); }
    bool GameConfig::Save(data::xml::XmlNode root_node) { return GameConfig::Save(*this, root_node); }

}