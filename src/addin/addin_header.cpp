/*
File: AddinHeader.cpp
Author: Lars Vidar Magnusson
 */

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <cstdint>

#include <pugixml.hpp>

#include "../global.h"
#include "../lib/file_path.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/content.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "../framework/system_info.h"
#include "../framework/component_info.h"
#include "addin_header.h"

namespace game::addin {

    AddinHeader::AddinHeader(const std::string& filename) : content::XmlContent(filename), type_(AddinType::System) {}
    AddinHeader::~AddinHeader() {}

    AddinType AddinHeader::GetType() { return this->type_; }
    const std::string& AddinHeader::GetLibraryFilename() { return this->library_filename_; }

    const std::vector<std::reference_wrapper<const framework::SystemInfo>> AddinHeader::GetSystemInfos() const {
        return std::vector<std::reference_wrapper<const framework::SystemInfo>>(system_infos_.begin(), system_infos_.end());
    }

    const std::vector<std::reference_wrapper<const framework::ComponentInfo>> AddinHeader::GetComponentInfos() const {
        return std::vector<std::reference_wrapper<const framework::ComponentInfo>>(component_infos_.begin(), component_infos_.end());
    }

    bool AddinHeader::Load(content::xml::XmlNode root_node) {

        if (root_node.GetName()!=XMLNAME_ADDINHEADER)
            return false;

        content::xml::XmlAttribute library_attribute = root_node.GetAttribute(XMLNAME_ADDINHEADER_LIBRARYFILENAME);
        if (!library_attribute)
            return false;
        library_filename_ = library_attribute.GetValue();

        content::xml::XmlNode name_node = root_node.GetChild(XMLNAME_ADDINHEADER_NAME);
        if (!name_node)
            return false;
        SetName(name_node.GetValue());

        content::xml::XmlNode description_node = root_node.GetChild(XMLNAME_ADDINHEADER_DESCRIPTION);
        if (!description_node)
            return false;
        SetDescription(description_node.GetValue());

        content::xml::XmlNode version_node = root_node.GetChild(XMLNAME_ADDINHEADER_VERSION);
        if (!version_node)
            return false;
        SetVersion(Version(version_node));

        // For now, only engine_ components addins are supported
        if (!root_node.HasChild(XMLNAME_ADDINHEADER_SYSTEM))
            return false;

        type_ = AddinType::System;

        for (content::xml::XmlNode system_node : root_node.GetChildren(XMLNAME_ADDINHEADER_SYSTEM)) {
            system_infos_.push_back(framework::SystemInfo(system_node));
        }

        for (content::xml::XmlNode component_node : root_node.GetChildren(XMLNAME_ADDINHEADER_COMPONENT)) {
            component_infos_.push_back(framework::ComponentInfo(component_node));
        }

        return true;

    }

    bool AddinHeader::Save(content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_ADDINHEADER);

        content::xml::XmlAttribute library_attribute = root_node.AddAttribute(XMLNAME_ADDINHEADER_LIBRARYFILENAME);
        library_attribute.SetValue(library_filename_.c_str());

        for (framework::SystemInfo& info:system_infos_)
            info.Save(root_node.AddChild());

        return true;

    }

    AddinHeader::Loader AddinHeader::Loader::singleton;

    AddinHeader::Loader::Loader() { Content::RegisterType(EXTENSION_ADDIN, &singleton); }

    content::Content* AddinHeader::Loader::Load(const std::string& filename) {

        AddinHeader* addin_header = new AddinHeader(filename);

        if (!((XmlContent*)addin_header)->Load())
            return nullptr;

        return addin_header;

    }

    uint32_t operator&(uint32_t lhs, AddinType rhs) {
        return lhs & static_cast<uint32_t>(rhs);
    }

    uint32_t operator|(uint32_t lhs, AddinType rhs) {
        return lhs | static_cast<uint32_t>(rhs);
    }

    uint32_t operator|(AddinType lhs, AddinType rhs) {
        return static_cast<uint32_t>(lhs)|static_cast<uint32_t>(rhs);;
    }

    uint32_t& operator<<=(uint32_t& lhs, AddinType rhs) {
        lhs = static_cast<uint32_t>(rhs);
        return lhs;
    }

}
