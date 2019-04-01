/*
File: XMLData.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

XMLData::XMLData(const string &filename, pugi::xml_document document)
    : Data(filename) {
    this->xmlDocument = document;
}

XMLData *XMLData::LoadXML() {

    xml_parse_result result = xmlDocument.load_file(filename.c_str());
    if (!result) {
        return false;    
    }

    return true;

}

void XMLData::SaveXML() {

    xmlDocument.save_file(filename.c_str()); 

    return true;

}

xml_document XMLData::GetXMLDocument() { return xmlDocument; }
void XMLData::SetXMLDocument(pugi::xml_document document) { this->xmlDocument = document; }

XMLData::XMLDataFactory::XMLDataFactory() { Data::RegisterType(extension, &singleton); }

XMLData *XMLData::XMLDataFactory::Load(const string &filename) {}
