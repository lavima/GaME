/*
File: AddinHeader.cpp
Author: Lars Vidar Magnusson
 */

#include "../GaME.h"

namespace game::addin {

    AddinType AddinHeader::GetType() { return this->type_; }
    const string& AddinHeader::GetLibraryFilename() { return this->library_filename_; }

    const vector<reference_wrapper<const SystemVersionInfo>> AddinHeader::GetSystemInfos() const {
        return vector<reference_wrapper<const SystemVersionInfo>>(system_infos_.begin(), system_infos_.end());
    }

    bool AddinHeader::Load(data::xml::XmlNode root_node) {

        if (root_node.GetName()!=XMLNAME_ADDININFO)
            return false;

        data::xml::XmlAttribute library_attribute = root_node.GetAttribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
        if (!library_attribute)
            return false;
        library_filename_ = library_attribute.GetValue();

        data::xml::XmlNode name_node = root_node.GetChild(XMLNAME_ADDININFO_NAME);
        if (!name_node)
            return false;
        SetName(name_node.GetValue());

        data::xml::XmlNode description_node = root_node.GetChild(XMLNAME_ADDININFO_DESCRIPTION);
        if (!description_node)
            return false;
        SetDescription(description_node.GetValue());

        data::xml::XmlNode version_node = root_node.GetChild(XMLNAME_ADDININFO_VERSION);
        if (!version_node)
            return false;
        SetVersion(Version(version_node));

        // For now, only engine_ components addins are supported
        if (!root_node.HasChild(XMLNAME_ADDININFO_ENGINECOMPONENT))
            return false;

        type_ = AddinType::System;

        for (data::xml::XmlNode system_node : root_node.GetChildren(XMLNAME_ADDININFO_ENGINECOMPONENT)) {
            system_infos_.push_back(SystemVersionInfo(system_node));
        }

        return true;

    }

    bool AddinHeader::Save(data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_ADDININFO);

        data::xml::XmlAttribute library_attribute = root_node.AddAttribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
        library_attribute.SetValue(library_filename_.c_str());

        for (SystemVersionInfo& info:system_infos_)
            info.Save(root_node.AddChild());

        return true;

    }

    AddinHeader::Loader AddinHeader::Loader::singleton;

    AddinHeader::Loader::Loader() { Data::RegisterType(EXTENSION_ADDIN, &singleton); }

    data::Data* AddinHeader::Loader::Load(const string& filename) {

        AddinHeader* addin_header = new AddinHeader(filename);

        if (!((XmlData*)addin_header)->Load())
            return nullptr;

        return addin_header;

    }

}