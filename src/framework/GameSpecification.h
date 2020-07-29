#pragma once

namespace game::framework {

#define EXTENSION_GAME "game"

#define XMLNAME_GAME "Game"
#define XMLNAME_GAME_HEADER XMLNAME_GAMEHEADER
#define XMLNAME_GAME_CONFIG XMLNAME_GAMECONFIG
#define XMLNAME_GAME_ENTITY XMLNAME_ENTITY

    class GAME_API GameSpecification: public data::XmlData{
        friend class Game;
    private:

        unique_ptr<GameHeader> header_;
        unique_ptr<GameConfig> config_;

        unordered_map<string, unique_ptr<EntitySpecification>> entities_;

    public:

        GameSpecification(const string& filename) : XmlData(filename) {}

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

        using XmlData::Load;
        using XmlData::Save;

    private:

        class Loader : ILoader {
        private:
            static Loader singleton_;
            Loader();
        public:
            Data* Load(const string& filename);
        };


    };

}