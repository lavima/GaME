/*
File: SystemInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define XMLNAME_SYSTEMVERSIONINFO string("System")

    class GAME_API SystemInfo : public VersionInfo {
    public:

        SystemInfo(const string& name, const string& description, const Version& version);
        SystemInfo(data::xml::XmlNode root_node);

    };

}