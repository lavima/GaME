/*
File: ComponentInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

#define XMLNAME_COMPONENINFO std::string("Component")

    class GAME_API ComponentInfo : public VersionInfo {
    public:

        ComponentInfo(const std::string& name, const std::string& description, const Version& version);
        ComponentInfo(content::xml::XmlNode root_node);

    };

}
