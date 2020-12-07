/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

#define XMLNAME_GAMEHEADER std::string("Header")
#define XMLNAME_GAMEHEADER_SYSTEM XMLNAME_SYSTEMVERSIONINFO 

    /*
    * GameHeader contains version information. Contains game title, description and the
    * game version along with the version information for the engine_ components required
    * to run the game.
    */
    class GAME_API GameHeader : public VersionInfo {
    private:

        std::vector<SystemInfo> required_systems_;

    public:

        GameHeader() : VersionInfo(XMLNAME_GAMEHEADER) {}
        GameHeader(content::xml::XmlNode root_node);

        static bool Load(GameHeader* info, content::xml::XmlNode root_node);
        static bool Save(GameHeader& info, content::xml::XmlNode root_node);

        void AddRequiredSystem(SystemInfo& component);

        const std::vector<std::reference_wrapper<const SystemInfo>> GetRequiredSystems() const;

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

    };

}
