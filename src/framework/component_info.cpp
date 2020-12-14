/*
File: ComponentInfo.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../lib/file_path.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "component_info.h"

namespace game::framework {

    ComponentInfo::ComponentInfo(const std::string& name, const std::string& description, const Version& version)
        : VersionInfo(name, description, version) {}

    ComponentInfo::ComponentInfo(content::xml::XmlNode root_node) : VersionInfo(root_node, XMLNAME_COMPONENINFO) {}

}
