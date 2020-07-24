/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

#define XMLNAME_GAMEHEADER string("Header")
#define XMLNAME_GAMEHEADER_ENGINECOMPONENT XMLNAME_SYSTEMVERSIONINFO 

    /*
    * GameHeader contains version information. Contains game title, description and the
    * game version along with the version information for the engine_ components required
    * to run the game.
    */
    class GAME_API GameHeader : public VersionInfo {
    private:

        vector<SystemVersionInfo> required_components_;

    public:

        GameHeader() : VersionInfo(XMLNAME_GAMEHEADER) {}
        GameHeader(data::xml::XmlNode root_node);

        static bool Load(GameHeader* info, data::xml::XmlNode root_node);
        static bool Save(GameHeader& info, data::xml::XmlNode root_node);

        void AddRequiredComponent(SystemVersionInfo& component);

        const vector<reference_wrapper<const SystemVersionInfo>> GetRequiredComponents() const;

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

    };

}