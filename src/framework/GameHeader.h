/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_GAMEHEADER string("Header")
#define XMLNAME_GAMEHEADER_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTINFO 

/*
* GameHeader contains version information. Contains game title, description and the 
* game version along with the version information for the engine_ components required
* to run the game.
*/
class GameHeader : public VersionInfo {
private:
    
    vector<EngineComponentVersionInfo> required_components_;

public:

    GameHeader() : VersionInfo(XMLNAME_GAMEHEADER) {}
    GameHeader(XmlNode root_node);

    static bool Load(GameHeader *info, XmlNode root_node);
    static bool Save(GameHeader &info, XmlNode root_node);

    void AddRequiredComponent(EngineComponentVersionInfo&component);

    const vector<reference_wrapper<const EngineComponentVersionInfo>> GetRequiredComponents() const;

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

};
