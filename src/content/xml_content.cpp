/*
File: XMLData.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "content.h"
#include "xml/xml_range.h"
#include "xml/xml_attribute.h"
#include "xml/xml_node.h"
#include "xml/xml_document.h"
#include "xml/xml_serializable.h"
#include "xml_content.h"

namespace game::content {

    XmlContent::XmlContent(const std::string& filename) : WritableContent(filename), xml_document_(xml::XmlDocument()) {}

    XmlContent::XmlContent(const std::string& filename, xml::XmlDocument document) : WritableContent(filename), xml_document_(document) {}

    bool XmlContent::Load() {

        if (!xml_document_.Load(GetFilename()))
            return false;

        return Load(xml_document_.GetDocumentElement());

    }

    bool XmlContent::Save() {

        Save(xml_document_.GetDocumentElement());

        return xml_document_.Save(GetFilename());

    }

    void XmlContent::Unload() {
        xml_document_.Unload();
    }

    xml::XmlDocument XmlContent::GetDocument() { return xml_document_; }

    //XmlContent::ICreator XmlContent::ICreator::singleton_;
    //XmlContent::ICreator::ICreator() { Data::RegisterType(EXTENSION_XML, &singleton_); }
    //Data * XmlContent::ICreator::Load(const string &filename_) {
    //    XmlContent* data = new XmlContent(filename_);
    //
    //    if (!data->Load())
    //        return nullptr;
    //
    //    return newGame;
    //}

}
