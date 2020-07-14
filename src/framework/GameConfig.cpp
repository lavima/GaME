/*
File: GameConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameConfig::GameConfig(XmlNode root_node) { assert(GameConfig::Load(this, root_node)); }

bool GameConfig::Load(GameConfig *config, XmlNode root_node) {

    if (root_node.GetName().compare(XMLNAME_GAMECONFIG))
        return false;

    for (XmlNode engine_component_config_node : root_node.GetChildren(XMLNAME_GAMECONFIG_ENGINECOMPONENT)) {

        EngineComponentConfig *component_config = EngineComponentConfig::Create(engine_component_config_node);
        if (!component_config)
            return false;

        config->engine_component_configs_.push_back(*component_config); 

    }
        
    return true;
}

bool GameConfig::Save(const GameConfig &config, XmlNode root_node) {

    return true;
}

const vector<reference_wrapper<EngineComponentConfig>> GameConfig::GetEngineComponentConfigs() { 
    return vector<reference_wrapper<EngineComponentConfig>>(engine_component_configs_.begin(), engine_component_configs_.end()); 
}

bool GameConfig::Load(XmlNode root_node) { return GameConfig::Load(this, root_node); }
bool GameConfig::Save(XmlNode root_node) { return GameConfig::Save(*this, root_node); }
