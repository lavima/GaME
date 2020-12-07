/*
File: GameHeader.h
Author: Lars Vidar Magnusson
*/

#include <vector>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../version.h"
#include "../version_info.h"
#include "system_info.h"
#include "game_header.h"


namespace game::framework {

    GameHeader::GameHeader(content::xml::XmlNode root_node) : VersionInfo(root_node, XMLNAME_GAMEHEADER) {}

    bool GameHeader::Load(GameHeader* header, content::xml::XmlNode root_node) {

        if (!VersionInfo::Load(header, root_node))
            return false;

        for (content::xml::XmlNode component_node : root_node.GetChildren(XMLNAME_GAMEHEADER_SYSTEM))
            header->required_systems_.push_back(SystemInfo(component_node));

        return true;

    }

    bool GameHeader::Save(GameHeader& header, content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_GAMEHEADER);

        for (SystemInfo& componentInfo:header.required_systems_)
            componentInfo.Save(root_node.AddChild(XMLNAME_GAMEHEADER_SYSTEM));

        return true;

    }

    void GameHeader::AddRequiredSystem(SystemInfo& component) { required_systems_.push_back(component); }

    const std::vector<std::reference_wrapper<const SystemInfo>> GameHeader::GetRequiredSystems() const {
        return std::vector<std::reference_wrapper<const SystemInfo>>(required_systems_.begin(), required_systems_.end());
    }

    bool GameHeader::Load(content::xml::XmlNode root_node) { return GameHeader::Load(this, root_node); }
    bool GameHeader::Save(content::xml::XmlNode root_node) { return GameHeader::Save(*this, root_node); }

}
