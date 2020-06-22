/*
File: XMLData.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

XMLData::XMLData(const string &filename) : WritableData(filename) {
    xmlDocument = unique_ptr<xml_document>(new xml_document());
}

XMLData::XMLData(const string &filename, pugi::xml_document *document) : WritableData(filename) {
    xmlDocument = unique_ptr<xml_document>(document);
}

bool XMLData::Load() {

    xml_parse_result result = xmlDocument->load_file(GetFilename().c_str());
    if (!result) {
        return false;    
    }

    return Load(xmlDocument->document_element());

}

bool XMLData::Save() {

    Save(xmlDocument->document_element());

    return xmlDocument->save_file(GetFilename().c_str()); 

}

bool XMLData::Parse(const string &filename, xml_document *document) {

    document = new xml_document();
    xml_parse_result result = document->load_file(filename.c_str());
    return (bool)result;

}

xml_document &XMLData::GetXMLDocument() { return *xmlDocument; }

XMLData::__Factory XMLData::__Factory::singleton;
XMLData::__Factory::__Factory() { Data::RegisterType("xml", &singleton); }
Data *XMLData::__Factory::Load(const string &filename) {}
