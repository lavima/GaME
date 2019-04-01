/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

EngineConfig(const string &filename) : XMLData(filename) {}

EngineConfig::EngineConfig(const string &filename, const string &logFilename) : XMLData(filaname) {

    this->logFilename = unique_ptr(new string(logFilename));

}

EngineConfig *Load(const string &filename) { return Data<EngineConfig>::Load(filename); }

const string &EngineConfig::GetLogFilename() { return logFilename; }
void EngineConfig::SetLogFilename(const string &logFilename) { this->logFilename = logFilename; }

void EngineConfig::AddAddinFilename(const string &addinFilename) { addinFilenames.push_back(addinFilename); }
const vector<reference_wrapper<const string>> EngineConfig::GetAddinFilenames() { return vector(addinFilenames.begin(), addinFilenames.end()); }

bool EngineConfig::Load() {

    if (!LoadXML())
        return false;

    xml_node nodeLogFilename = GetXMLDocument.child("LogFilename")    
    if (!nodeLogFilename.empty())
        this->logFilename = string(nodeLogFilename.value());

    for (xml_node addinNode = GetXMLDocument.child("Addin"); addinNode; addinNode = addinNode.next_sibling("Addin"))
        this->addinFilenames.push_back(string(addinNode.value()));

    return true;

}

bool EngineConfig::Save() {

    if (!SaveXML())
        return false;

    return true;
}


EngineConfigFactory EngineConfigFactory::singleton;

EngineConfig::EngineConfigFactory::EngineConfigFactory() { Data::RegisterType(ENGINE_CONFIG_EXTENSION, &singleton); }                                                                        
EngineConfig *EngineConfig::EngineConfigFactory::Load(const string &filename) { 

    EngineConfig newConfig = new EngineConfig(filename);

    if (!newConfig->Load())
        return nullptr;

    return newConfig;

}
