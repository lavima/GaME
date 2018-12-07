/*
File: GameConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

class GameConfig {

private:

    unordered_map<string, string> engineComponents;

    GameConfig() {}

public:

    static GameConfig *Load(pugi::xml_node &xmlNode);

    unordered_map<string, string> &GetEngineComponents();

};
