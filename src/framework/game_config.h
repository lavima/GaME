/*
File: GameConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::framework {

#define XMLNAME_GAMECONFIG "Config"
#define XMLNAME_GAMECONFIG_SYSTEM XMLNAME_SYSTEMCONFIG

    class GAME_API GameConfig : content::xml::IXmlSerializable {
    private:

        std::vector<SystemConfig> system_configs_;

    public:

        GameConfig() {}
        GameConfig(content::xml::XmlNode root_node);

        static bool Load(GameConfig* config, content::xml::XmlNode root_node);
        static bool Save(const GameConfig& config, content::xml::XmlNode root_node);

        const std::vector<std::reference_wrapper<SystemConfig>> GetSystemConfigs();

        bool Load(content::xml::XmlNode root_node);
        bool Save(content::xml::XmlNode root_node);

    };

}
