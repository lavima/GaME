/*
File: XMLData.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

XmlData::XmlData(const string &filename) : WritableData(filename), xml_document_(XmlDocument()) {}

XmlData::XmlData(const string &filename, XmlDocument document) : WritableData(filename), xml_document_(document) {}

bool XmlData::Load() {

    if (!xml_document_.Load(GetFilename())) 
        return false;    

    return Load(xml_document_.GetDocumentElement());

}

bool XmlData::Save() {

    Save(xml_document_.GetDocumentElement());

    return xml_document_.Save(GetFilename()); 

}

XmlDocument XmlData::GetDocument() { return xml_document_; }

//XmlData::Loader XmlData::Loader::singleton_;
//XmlData::Loader::Loader() { Data::RegisterType(EXTENSION_XML, &singleton_); }
//Data * XmlData::Loader::Create(const string &filename_) {
//    XmlData* data = new XmlData(filename_);
//
//    if (!data->Create())
//        return nullptr;
//
//    return newGame;
//}
