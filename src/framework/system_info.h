/*
File: SystemInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

#define XMLNAME_SYSTEMVERSIONINFO std::string("System")

    class GAME_API SystemInfo final : public VersionInfo {
    public:

        SystemInfo(const std::string& name, const std::string& description, const Version& version);
        SystemInfo(content::xml::XmlNode root_node);


    };

}
