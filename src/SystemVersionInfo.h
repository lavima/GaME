/*
File: SystemVersionInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define XMLNAME_SYSTEMVERSIONINFO string("System")

    class GAME_API SystemVersionInfo : public VersionInfo {
    public:

        SystemVersionInfo(const string& name, const string& description, const Version& version);
        SystemVersionInfo(data::xml::XmlNode root_node);

    };

}