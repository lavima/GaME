/*
File: AddinHeader.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

AddinType AddinHeader::GetType() { return this->type_; }
const string &AddinHeader::GetLibraryFilename() { return this->library_filename_; }

const vector<reference_wrapper<const EngineComponentVersionInfo>> AddinHeader::GetEngineComponents() const { 
    return vector<reference_wrapper<const EngineComponentVersionInfo>>(engine_components_.begin(), engine_components_.end());
}

bool AddinHeader::Load(XmlNode root_node) {

    if (root_node.GetName()!=XMLNAME_ADDININFO)
        return false;

    XmlAttribute library_attribute = root_node.GetAttribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
    if (!library_attribute)
        return false;
    library_filename_ = library_attribute.GetValue();

    XmlNode name_node = root_node.GetChild(XMLNAME_ADDININFO_NAME);
    if (!name_node)
        return false;
    SetName(name_node.GetValue());

    XmlNode description_node = root_node.GetChild(XMLNAME_ADDININFO_DESCRIPTION);
    if (!description_node)
        return false;
    SetDescription(description_node.GetValue());

    XmlNode version_node = root_node.GetChild(XMLNAME_ADDININFO_VERSION);
    if (!version_node)
        return false;
    SetVersion(Version(version_node));

    // For now, only engine_ components addins are supported
    if (!root_node.HasChild(XMLNAME_ADDININFO_ENGINECOMPONENT))
        return false;
    
    type_ = AddinType::EngineComponent;       

    for (XmlNode component_node : root_node.GetChildren(XMLNAME_ADDININFO_ENGINECOMPONENT)) {
        engine_components_.push_back(EngineComponentVersionInfo(component_node));
    }

    return true;

}

bool AddinHeader::Save(XmlNode root_node) {

    root_node.SetName(XMLNAME_ADDININFO);

    XmlAttribute library_attribute = root_node.AddAttribute(XMLNAME_ADDININFO_LIBRARYFILENAME);
    library_attribute.SetValue(library_filename_.c_str());

    for (EngineComponentVersionInfo &component_info : engine_components_) 
        component_info.Save(root_node.AddChild());

    return true;

}

AddinHeader::Loader AddinHeader::Loader::singleton;

AddinHeader::Loader::Loader() { Data::RegisterType(EXTENSION_ADDIN, &singleton); }

Data *AddinHeader::Loader::Load(const string &filename) { 

    AddinHeader *addin_header = new AddinHeader(filename);

    if (!((XmlData *)addin_header)->Load())
        return nullptr;

    return addin_header;

}
