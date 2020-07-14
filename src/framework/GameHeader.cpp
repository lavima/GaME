/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameHeader::GameHeader(XmlNode root_node) : VersionInfo(root_node, XMLNAME_GAMEHEADER) {}

bool GameHeader::Load(GameHeader *header, XmlNode root_node) {

    if (!VersionInfo::Load(header, root_node))
        return false;

    for (XmlNode component_node : root_node.GetChildren(XMLNAME_GAMEHEADER_ENGINECOMPONENT))
        header->required_components_.push_back(EngineComponentVersionInfo(component_node));

    return true;
  
}

bool GameHeader::Save(GameHeader &header, XmlNode root_node) {

    root_node.SetName(XMLNAME_GAMEHEADER);

    for (EngineComponentVersionInfo& componentInfo : header.required_components_)
        componentInfo.Save(root_node.AddChild(XMLNAME_GAMEHEADER_ENGINECOMPONENT));

    return true;

}

void GameHeader::AddRequiredComponent(EngineComponentVersionInfo& component) { required_components_.push_back(component); }

const vector<reference_wrapper<const EngineComponentVersionInfo>> GameHeader::GetRequiredComponents() const {
    return vector<reference_wrapper<const EngineComponentVersionInfo>>(required_components_.begin(), required_components_.end());
}

bool GameHeader::Load(XmlNode root_node) { return GameHeader::Load(this, root_node); }
bool GameHeader::Save(XmlNode root_node) { return GameHeader::Save(*this, root_node); }
