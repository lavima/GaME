/*
File: XMLData.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

namespace game::data {

    XmlData::XmlData(const string& filename) : WritableData(filename), xml_document_(xml::XmlDocument()) {}

    XmlData::XmlData(const string& filename, xml::XmlDocument document) : WritableData(filename), xml_document_(document) {}

    bool XmlData::Load() {

        if (!xml_document_.Load(GetFilename()))
            return false;

        return Load(xml_document_.GetDocumentElement());

    }

    bool XmlData::Save() {

        Save(xml_document_.GetDocumentElement());

        return xml_document_.Save(GetFilename());

    }

    void XmlData::Unload() {
        xml_document_.Unload();
    }

    xml::XmlDocument XmlData::GetDocument() { return xml_document_; }

    //XmlData::ICreator XmlData::ICreator::singleton_;
    //XmlData::ICreator::ICreator() { Data::RegisterType(EXTENSION_XML, &singleton_); }
    //Data * XmlData::ICreator::Load(const string &filename_) {
    //    XmlData* data = new XmlData(filename_);
    //
    //    if (!data->Load())
    //        return nullptr;
    //
    //    return newGame;
    //}

}