/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_GAMEHEADER string("Header")
#define XMLNAME_GAMEHEADER_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTINFO 

/*
* Game version_ information. Specifies a game_ header containing game_ title, description_ and the 
* game_ version_ along wit the engine_ components_ required to run the game_.
*/
class GameHeader : public VersionInfo {
private:
    
    vector<EngineComponentVersionInfo> requiredEngineComponents;

public:

    GameHeader() {}
    GameHeader(XmlNode root_node);

    static bool Load(GameHeader *info, XmlNode root_node);
    static bool Save(GameHeader &info, XmlNode root_node);

    void AddRequiredComponent(EngineComponentVersionInfo&component);

    const vector<reference_wrapper<const EngineComponentVersionInfo>> GetRequiredComponents() const;

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

};
