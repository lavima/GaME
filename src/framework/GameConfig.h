/*
File: GameConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::framework {

#define XMLNAME_GAMECONFIG "Config"
#define XMLNAME_GAMECONFIG_SYSTEM XMLNAME_SYSTEMCONFIG

    class GAME_API GameConfig : data::xml::IXmlSerializable {
    private:

        vector<SystemConfig> engine_component_configs_;

    public:

        GameConfig() {}
        GameConfig(data::xml::XmlNode root_node);

        static bool Load(GameConfig* config, data::xml::XmlNode root_node);
        static bool Save(const GameConfig& config, data::xml::XmlNode root_node);

        const vector<reference_wrapper<SystemConfig>> GetEngineComponentConfigs();

        bool Load(data::xml::XmlNode root_node);
        bool Save(data::xml::XmlNode root_node);

    };

}