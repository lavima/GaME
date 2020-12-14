#pragma once

namespace game::framework {

#define DEFAULT_GAME_NAME std::string("NewGame")

#define EXTENSION_GAME std::string("game")

#define XMLNAME_GAME std::string("Game")
#define XMLNAME_GAME_HEADER XMLNAME_GAMEHEADER
#define XMLNAME_GAME_CONFIG XMLNAME_GAMECONFIG
#define XMLNAME_GAME_ENTITY XMLNAME_ENTITY
#define XMLNAME_GAME_ENTITY_FILENAME "filename"

    class GAME_API GameSpecification: public content::XmlContent{
        friend class Game;
    private:

        std::unique_ptr<GameHeader> header_;
        std::unique_ptr<GameConfig> config_;

        std::unordered_map<std::string, EntitySpecification*> entities_;


        GameSpecification();
        GameSpecification(const std::string& filename);

    public:

        virtual ~GameSpecification();

        static GameSpecification* Create();


        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

        using XmlContent::Load;
        using XmlContent::Save;

        const std::vector<std::reference_wrapper<EntitySpecification>> GetEntities() const;

    private:

        class Loader : ILoader {
        private:
            static Loader singleton_;
            Loader();
        public:
            content::Content* Load(const std::string& filename) override;
        };


    };

}
