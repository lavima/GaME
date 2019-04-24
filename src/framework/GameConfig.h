/*
File: GameConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define XMLNAME_GAMECONFIG "GameConfig"
#define XMLNAME_GAMECONFIG_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTCONFIG

class GameConfig : XMLSerializable {
private:

    vector<EngineComponentConfig *> engineComponentConfigs;

public:

    GameConfig() {} 
    GameConfig(pugi::xml_node rootNode);

    static bool Load(GameConfig *config, pugi::xml_node rootNode);
    static bool Save(GameConfig &config, pugi::xml_node rootNode);

    const vector<EngineComponentConfig *> &GetEngineComponentConfigs();

    bool Load(pugi::xml_node rootNode);
    bool Save(pugi::xml_node rootNode);

};
