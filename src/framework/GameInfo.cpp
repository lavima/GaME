/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

GameInfo::GameInfo(xml_node rootNode) { assert(GameInfo::Load(this, rootNode)); }

bool GameInfo::Load(GameInfo *info, xml_node rootNode) {

    if (string(rootNode.name()).compare(XMLNAME_GAMEINFO))
        return false;

    xml_node componentNode = rootNode.child(XMLNAME_GAMEINFO_ENGINECOMPONENT);
    for ( ; componentNode; componentNode = componentNode.next_sibling(XMLNAME_GAMEINFO_ENGINECOMPONENT))
        info->requiredEngineComponents.push_back(EngineComponentInfo(componentNode));

    return true;
  
}

bool GameInfo::Save(GameInfo &info, xml_node rootNode) {

    rootNode.set_name(XMLNAME_GAMEINFO);

    for (EngineComponentInfo &componentInfo : info.requiredEngineComponents)
        componentInfo.Save(rootNode.append_child(XMLNAME_GAMEINFO_ENGINECOMPONENT));

    return true;

}

void GameInfo::AddRequiredComponent(EngineComponentInfo &component) { requiredEngineComponents.push_back(component); }

const vector<reference_wrapper<const EngineComponentInfo>> GameInfo::GetRequiredComponents() const { 
    return vector<reference_wrapper<const EngineComponentInfo>>(requiredEngineComponents.begin(), requiredEngineComponents.end()); 
}

bool GameInfo::Load(xml_node rootNode) { GameInfo::Load(this, rootNode); }
bool GameInfo::Save(xml_node rootNode) { GameInfo::Save(*this, rootNode); }
