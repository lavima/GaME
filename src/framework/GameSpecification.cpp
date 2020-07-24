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

        return true;

    }

    bool GameSpecification::Save(data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_GAME);

        if (!header_->Save(root_node.AddChild()))
            return false;

        if (!config_->Save(root_node.AddChild()))
            return false;

        return true;
    }

    GameSpecification::Loader GameSpecification::Loader::singleton;

    GameSpecification::Loader::Loader() { Data::RegisterType(EXTENSION_GAME, &singleton); }

    data::Data* GameSpecification::Loader::Load(const string& filename) {

        GameSpecification* newGame = new GameSpecification(filename);

        if (!newGame->Load())
            return nullptr;

        return newGame;

    }

}