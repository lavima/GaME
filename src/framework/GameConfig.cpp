/*
File: GameConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameConfig::GameConfig(pugi::xml_node rootNode) { assert(GameConfig::Load(this, rootNode)); }

bool GameConfig::Load(GameConfig *config, pugi::xml_node rootNode) {

    if (string(rootNode.name()).compare(XMLNAME_GAMECONFIG))
        return false;

    xml_node engineComponentConfigNode = rootNode.child(XMLNAME_GAMECONFIG_ENGINECOMPONENT);
    while (engineComponentConfigNode) {

        EngineComponentConfig *config = EngineComponentConfig::Load(engineComponentConfigNode);
        if (!config)
            return false;

        engineComponentConfigs.push_back(); 

        engineComponentConfigNode = engineComponentConfigNode.next_sibling(XMLNAME_GAMECONFIG_ENGINECOMPONENT);

    }
        
    return true;
}

bool GameConfig::Save(GameConfig &config, pugi::xml_node rootNode) {

    return true;
}

const vector<EngineComponentConfig *> &GameConfig::GetEngineComponentConfigs() { return engineComponentConfigs; }

bool GameConfig::Load(pugi::xml_node rootNode) { return GameConfig::Load(this, rootNode); }
bool GameConfig::Save(pugi::xml_node rootNode) { return GameConfig::Save(*this, rootNode); }
