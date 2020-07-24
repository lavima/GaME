/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

namespace game::framework {

    GameHeader::GameHeader(data::xml::XmlNode root_node) : VersionInfo(root_node, XMLNAME_GAMEHEADER) {}

    bool GameHeader::Load(GameHeader* header, data::xml::XmlNode root_node) {

        if (!VersionInfo::Load(header, root_node))
            return false;

        for (data::xml::XmlNode component_node : root_node.GetChildren(XMLNAME_GAMEHEADER_ENGINECOMPONENT))
            header->required_components_.push_back(SystemVersionInfo(component_node));

        return true;

    }

    bool GameHeader::Save(GameHeader& header, data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_GAMEHEADER);

        for (SystemVersionInfo& componentInfo:header.required_components_)
            componentInfo.Save(root_node.AddChild(XMLNAME_GAMEHEADER_ENGINECOMPONENT));

        return true;

    }

    void GameHeader::AddRequiredComponent(SystemVersionInfo& component) { required_components_.push_back(component); }

    const vector<reference_wrapper<const SystemVersionInfo>> GameHeader::GetRequiredComponents() const {
        return vector<reference_wrapper<const SystemVersionInfo>>(required_components_.begin(), required_components_.end());
    }

    bool GameHeader::Load(data::xml::XmlNode root_node) { return GameHeader::Load(this, root_node); }
    bool GameHeader::Save(data::xml::XmlNode root_node) { return GameHeader::Save(*this, root_node); }

}