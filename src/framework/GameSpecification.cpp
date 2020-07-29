#include "../GaME.h"

namespace game::framework {

    bool GameSpecification::Load(data::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_GAME))
            return false;

        data::xml::XmlNode header_node = root_node.GetChild(XMLNAME_GAME_HEADER);
        header_ = unique_ptr<GameHeader>(new GameHeader());
        if (!header_->Load(header_node))
            return false;

        data::xml::XmlNode config_node = root_node.GetChild(XMLNAME_GAME_CONFIG);
        config_ = unique_ptr<GameConfig>(new GameConfig());
        if (!config_->Load(config_node))
            return false;

        for (auto entity_node:root_node.GetChildren(XMLNAME_GAME_ENTITY)) {

            EntitySpecification* entity = Data::Load<EntitySpecification>(root_node.GetValue());
            
            if (!entity)
                return false;

            entities_.insert_or_assign(entity->GetName(), unique_ptr<EntitySpecification>(entity));

        }

        return true;

    }

    bool GameSpecification::Save(data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_GAME);

        if (!header_->Save(root_node.AddChild()))
            return false;

        if (!config_->Save(root_node.AddChild()))
            return false;

        for (const auto& [name, entity]:entities_) {

            if (!entity->Save())
                return false;

            data::xml::XmlNode entity_node = root_node.AddChild();
            entity_node.SetValue(entity->GetFilename());

        }

        return true;
    }

    GameSpecification::Loader GameSpecification::Loader::singleton_;

    GameSpecification::Loader::Loader() { Data::RegisterType(EXTENSION_GAME, &singleton_); }

    data::Data* GameSpecification::Loader::Load(const string& filename) {

        GameSpecification* newGame = new GameSpecification(filename);

        if (!newGame->Load())
            return nullptr;

        return newGame;

    }

}