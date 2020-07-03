#pragma once

#define EXTENSION_GAME "game"

#define XMLNAME_GAME "Game"
#define XMLNAME_GAME_INFO XMLNAME_GAMEHEADER
#define XMLNAME_GAME_CONFIG XMLNAME_GAMECONFIG

class GameSpecification : public XmlData {
    friend class Game;
private:

    unique_ptr<GameHeader> header_; 
    unique_ptr<GameConfig> config_;

public:

    GameSpecification(const string& filename) : XmlData(filename) {}

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

    using XmlData::Load;
    using XmlData::Save;

private:

    class Loader : DataLoader {
    private:

        static Loader singleton;

        Loader();

    public:

        Data* Load(const string& filename);

    };


};