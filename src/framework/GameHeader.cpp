/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameHeader::GameHeader(XmlNode root_node) { assert(GameHeader::Load(this, root_node)); }

bool GameHeader::Load(GameHeader *info, XmlNode root_node) {

    if (root_node.GetName().compare(XMLNAME_GAMEHEADER))
        return false;

    for (XmlNode component_node : root_node.GetChildren(XMLNAME_GAMEHEADER_ENGINECOMPONENT))
        info->requiredEngineComponents.push_back(EngineComponentVersionInfo(component_node));

    return true;
  
}

bool GameHeader::Save(GameHeader &info, XmlNode root_node) {

    root_node.SetName(XMLNAME_GAMEHEADER);

    for (EngineComponentVersionInfo& componentInfo : info.requiredEngineComponents)
        componentInfo.Save(root_node.AddChild(XMLNAME_GAMEHEADER_ENGINECOMPONENT));

    return true;

}

void GameHeader::AddRequiredComponent(EngineComponentVersionInfo& component) { requiredEngineComponents.push_back(component); }

const vector<reference_wrapper<const EngineComponentVersionInfo>> GameHeader::GetRequiredComponents() const {
    return vector<reference_wrapper<const EngineComponentVersionInfo>>(requiredEngineComponents.begin(), requiredEngineComponents.end());
}

bool GameHeader::Load(XmlNode root_node) { return GameHeader::Load(this, root_node); }
bool GameHeader::Save(XmlNode root_node) { return GameHeader::Save(*this, root_node); }
