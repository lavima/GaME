/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

EngineConfig::EngineConfig(const string &filename, const string &logFilename) {

    this->filename = filename;
    this->logFilename = logFilename;

}

EngineConfig::EngineConfig(const string &filename, const string &logFilename, const vector<string> &addinFilenames) {

    this->filename = filename;
    this->logFilename = logFilename;
    this->addinFilenames = addinFilenames;

}

EngineConfig::EngineConfig(const string &filename) : EngineConfig(*PugiXML::ParseDocument(filename)) {}

EngineConfig::EngineConfig(pugi::xml_document &xmlDocument) {

    this->xmlDocument = &xmlDocument;

    for (xml_node addinNode = xmlDocument.child("Addin"); addinNode; addinNode = addinNode.next_sibling("Addin"))
        this->addinFilenames.push_back(string(addinNode.value()));

}

EngineConfig::~EngineConfig() {

}

void EngineConfig::AddAddinFilename(const string &addinFilename) { addinFilenames.push_back(addinFilename); }
const string &EngineConfig::GetFilename() { return filename; }
const string &EngineConfig::GetLogFilename() { return logFilename; }
const vector<string> &EngineConfig::GetAddinFilenames() { return addinFilenames; }
