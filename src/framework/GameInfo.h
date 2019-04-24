/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_GAMEINFO "GameInfo"
#define XMLNAME_GAMEINFO_ENGINECOMPONENT XMLNAME_ENGINECOMPONENTINFO 

/*
* Game information. Specifies the version and the engine components
* required to run a game.
*/
class GameInfo : public __InfoBase, public XMLSerializable {
private:
    
    vector<EngineComponentInfo> requiredEngineComponents;

public:

    GameInfo() {}
    GameInfo(pugi::xml_node rootNode);

    static bool Load(GameInfo *info, pugi::xml_node rootNode);
    static bool Save(GameInfo &info, pugi::xml_node rootNode);

    void AddRequiredComponent(EngineComponentInfo &component);

    const vector<reference_wrapper<const EngineComponentInfo>> GetRequiredComponents() const;

    bool Load(pugi::xml_node rootNode);
    bool Save(pugi::xml_node rootNode);

};
