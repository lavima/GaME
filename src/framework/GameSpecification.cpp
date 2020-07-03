#include "../GaME.h"

bool GameSpecification::Load(XmlNode root_node) {

    if (root_node.GetName().compare(XMLNAME_GAME))
        return false;

    XmlNode header_node = root_node.GetChild(XMLNAME_GAME_INFO);
    header_ = unique_ptr<GameHeader>(new GameHeader());
    if (!header_->Load(header_node))
        return false;

    XmlNode config_node = root_node.GetChild(XMLNAME_GAME_CONFIG);
    config_ = unique_ptr<GameConfig>(new GameConfig());
    if (!config_->Load(config_node))
        return false;

    return true;

}

bool GameSpecification::Save(XmlNode root_node) {

    root_node.SetName(XMLNAME_GAME);

    if (!header_->Save(root_node.AddChild()))
        return false;

    if (!config_->Save(root_node.AddChild()))
        return false;

    return true;
}

GameSpecification::Loader GameSpecification::Loader::singleton;

GameSpecification::Loader::Loader() { Data::RegisterType(EXTENSION_GAME, &singleton); }

Data* GameSpecification::Loader::Load(const string& filename) {

    GameSpecification* newGame = new GameSpecification(filename);

    if (!newGame->Load())
        return nullptr;

    return newGame;

}