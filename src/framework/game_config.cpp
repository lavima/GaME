/*
File: GameConfig.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <memory>
#include <optional>

#include <pugixml.hpp>

#include "../global.h"
#include "../lib/file_path.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "framework.h"
#include "system_config.h"
#include "game_config.h"

namespace game::framework {

    GameConfig::GameConfig() {}
    GameConfig::GameConfig(content::xml::XmlNode root_node) { assert(GameConfig::Load(this, root_node)); }
    GameConfig::~GameConfig() {}

    bool GameConfig::Load(GameConfig* config, content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_GAMECONFIG))
            return false;

        for (content::xml::XmlNode config_node : root_node.GetChildren(XMLNAME_GAMECONFIG_SYSTEM)) {

            SystemConfig* component_config = SystemConfig::Create(config_node);
            if (!component_config)
                return false;

            config->system_configs_.push_back(*component_config);

        }

        return true;
    }

    bool GameConfig::Save(const GameConfig& config, content::xml::XmlNode root_node) {

        return true;
    }

    const std::vector<std::reference_wrapper<SystemConfig>> GameConfig::GetSystemConfigs() {
        return std::vector<std::reference_wrapper<SystemConfig>>(system_configs_.begin(), system_configs_.end());
    }

    bool GameConfig::Load(content::xml::XmlNode root_node) { return GameConfig::Load(this, root_node); }
    bool GameConfig::Save(content::xml::XmlNode root_node) { return GameConfig::Save(*this, root_node); }

}
