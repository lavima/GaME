/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

EngineConfig::~EngineConfig() {

    document->release();

    delete platformConfig;
    for (int i = 0; i < addins.size(); i++)
        delete addins[i];

}

EngineConfig *EngineConfig::Load(const string &filename) {

    EngineConfig *engineConfig = new EngineConfig();
    engineConfig->document = Xerces::ParseDocument(filename);

    engineConfig->platformConfig = PlatformConfig::Load(engineConfig->document);

    xercesc::DOMNodeList *addinNodes = engineConfig->document->getElementsByTagName(XERCESTRANSCODE("Addin"));
    for (int i = 0; i < addinNodes->getLength(); i++)
        engineConfig->addins.push_back(AddinConfig::Load((xercesc::DOMElement *)addinNodes->item(i)));

    return engineConfig;

}

PlatformConfig &EngineConfig::GetPlatformConfig() { return *platformConfig; }
int EngineConfig::GetNumAddins() { return addins.size(); }
AddinConfig &EngineConfig::GetAddin(int index) { return *(addins[index]); }

AddinConfig *AddinConfig::Load(xercesc::DOMElement *element) {

    AddinConfig *ret = new AddinConfig();

    ret->source = new string(XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("source"))));

    return ret;

}

const string &AddinConfig::GetSource() { return *(this->source); }