/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

EngineConfig::EngineConfig(const string &filename) : XMLData(filename) {}

EngineConfig::EngineConfig(const string &filename, const string &logFilename) : XMLData(filename) {

    this->logFilename = unique_ptr<string>(new string(logFilename));

}

bool EngineConfig::HasLogFilename() { return (bool)logFilename; }
const string &EngineConfig::GetLogFilename() { return *logFilename; }
void EngineConfig::SetLogFilename(const string &logFilename) { this->logFilename.reset(new string(logFilename)); }

void EngineConfig::AddAddinFilename(const string &addinFilename) { addinFilenames.push_back(addinFilename); }
const vector<reference_wrapper<const string>> EngineConfig::GetAddinFilenames() { 
    return vector<reference_wrapper<const string>>(addinFilenames.begin(), addinFilenames.end()); 
}

bool EngineConfig::Load(xml_node rootNode) {

    if (string(rootNode.get_name()).compare(XMLNAME_ENGINECONFIG))
        return false

    xml_node nodeLogFilename = rootNode.child(XMLNAME_ENGINECONFIG_LOGFILENAME);
    if (nodeLogFilename)
        this->logFilename.reset(new string(nodeLogFilename.value()));

    for (xml_node addinNode = rootNode.child(XMLNAME_ENGINECONFIG_ADDIN); addinNode; addinNode = addinNode.next_sibling(XMLNAME_ENGINECONFIG_ADDIN))
        this->addinFilenames.push_back(string(addinNode.value()));

    return true;

}

bool EngineConfig::Save(xml_node rootNode) {

    rootNode.set_name(XMLNAME_ENGINECONFIG);

    if (logFilename) {
        xml_node logFilenameNode = rootNode.append_child(XMLNAME_ENGINECONFIG_LOGFILENAME);
        logFilenameNode.set_value(logFilename->c_str());
    }
        
    for (string addinFilename : addinFilenames) {
        xml_node addinFilenameNode = rootNode.append_child(XMLNAME_ENGINECONFIG_ADDIN);
        addinFilenameNode.set_value(addinFilename);
    }

    return true;

}


EngineConfig::__Factory EngineConfig::__Factory::singleton;

EngineConfig::__Factory::__Factory() { Data::RegisterType(EXTENSION_ENGINECONFIG, &singleton); }

Data *EngineConfig::__Factory::Load(const string &filename) { 

    EngineConfig *newConfig = new EngineConfig(filename);

    if (!newConfig->Load())
        return nullptr;

    return newConfig;

}
