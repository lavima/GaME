/*
File: GameConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define XMLNAME_GAMECONFIG "Config"
#define XMLNAME_GAMECONFIG_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTCONFIG

class GameConfig : XmlSerializable {
private:

    vector<EngineComponentConfig> engine_component_configs_;

public:

    GameConfig() {} 
    GameConfig(XmlNode root_node);

    static bool Load(GameConfig *config, XmlNode root_node);
    static bool Save(const GameConfig &config, XmlNode root_node);

    const vector<reference_wrapper<EngineComponentConfig>> GetEngineComponentConfigs();

    bool Load(XmlNode root_node);
    bool Save(XmlNode root_node);

};
