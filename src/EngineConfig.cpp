/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

EngineConfig::~EngineConfig() {

    document->save_file(configFilename->c_str());

    delete platformConfig;
    for (int i = 0; i < addins.size(); i++)
        delete addins[i];

}

EngineConfig *EngineConfig::Load(const string &filename) {

    EngineConfig *engineConfig = new EngineConfig();
    engineConfig->document = PugiXML::ParseDocument(filename);

    engineConfig->platformConfig = PlatformConfig::Load(engineConfig->document);

    for (xml_node addinNode = ngineConfig->document->child("Addin"); addinNode; addinNode = addinNode.next_sibling("Addin"))
        engineConfig->addins.push_back(AddinConfig::Load(addinNode));

    return engineConfig;

}

PlatformConfig &EngineConfig::GetPlatformConfig() { return *platformConfig; }
int EngineConfig::GetNumAddins() { return addins.size(); }
AddinConfig &EngineConfig::GetAddin(int index) { return *(addins[index]); }

AddinConfig *AddinConfig::Load(xml_node &element) {

    AddinConfig *ret = new AddinConfig();

    ret->source = new string(element.attribute("source").value());

    return ret;

}

const string &AddinConfig::GetSource() { return *(this->source); }
