#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>
#include <optional>
#include <algorithm>

#include <pugixml.hpp>
#include <v8.h>

#include "../global.h"
#include "../lib/file_path.h"
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

namespace game::framework {
    GameSpecification* GameSpecification::Create() {
        return new GameSpecification();
    }

    bool GameSpecification::Load(content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_GAME))
            return false;

        content::xml::XmlNode header_node = root_node.GetChild(XMLNAME_GAME_HEADER);
        header_ = std::unique_ptr<GameHeader>(new GameHeader());
        if (!header_->Load(header_node))
            return false;

        content::xml::XmlNode config_node = root_node.GetChild(XMLNAME_GAME_CONFIG);
        config_ = std::unique_ptr<GameConfig>(new GameConfig());
        if (!config_->Load(config_node))
            return false;

        for (auto entity_node:root_node.GetChildren(XMLNAME_GAME_ENTITY)) {

            content::xml::XmlAttribute filename_attrib = entity_node.GetAttribute(XMLNAME_GAME_ENTITY_FILENAME);

            EntitySpecification* entity = Content::Load<EntitySpecification>(filename_attrib.GetValue());
            if (!entity)
                return false;

            entities_.insert_or_assign(entity->GetName(), entity);

        }

        return true;

    }

    bool GameSpecification::Save(content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_GAME);

        if (!header_->Save(root_node.AddChild()))
            return false;

        if (!config_->Save(root_node.AddChild()))
            return false;

        for (const auto& [name, entity]:entities_) {

            if (!entity->Save())
                return false;

            content::xml::XmlNode entity_node = root_node.AddChild(XMLNAME_GAME_ENTITY);
            content::xml::XmlAttribute filename_attrib = entity_node.AddAttribute(XMLNAME_GAME_ENTITY_FILENAME);
            filename_attrib.SetValue(entity->GetFilename());

        }

        return true;
    }

    const std::vector<std::reference_wrapper<EntitySpecification>> GameSpecification::GetEntities() const {
        
        std::vector<std::reference_wrapper<EntitySpecification>> entities;
        
        transform(entities_.begin(), entities_.end(), back_inserter(entities),
            [&](const std::pair<const std::string, EntitySpecification*>& pair) {
                return std::reference_wrapper<EntitySpecification>(*pair.second); });

        return entities;

    }

    GameSpecification::Loader GameSpecification::Loader::singleton_;

    GameSpecification::Loader::Loader() { Content::RegisterType(EXTENSION_GAME, &singleton_); }

    content::Content* GameSpecification::Loader::Load(const std::string& filename) {

        GameSpecification* newGame = new GameSpecification(filename);

        if (!newGame->Load())
            return nullptr;

        return newGame;

    }

}
