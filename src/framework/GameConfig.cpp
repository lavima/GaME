/*
File: GameConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameConfig *GameConfig::Load(pugi::xml_node &xmlNode) {
  return new GameConfig();
}

unordered_map<string, string> &GameConfig::GetEngineComponents() {

}
