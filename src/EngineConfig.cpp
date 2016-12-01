/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>

#include <vector>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLString.hpp>

#include "lib/XercesUtils.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "EngineConfig.h"

EngineConfig::~EngineConfig() {

  document->release();

  delete platformConfig;
  for (int i=0; i<addins.size(); i++)
    delete addins[i];

}

EngineConfig *EngineConfig::Load(const char *filename) {

  EngineConfig *newEngineConfig = new EngineConfig();
  newEngineConfig->document = XercesParseDocument(filename);

  xercesc::DOMNodeList *platformConfigNodes = 
    newEngineConfig->document->getElementsByTagName(XERCESTRANSCODE("PlatformConfig"));
  if (platformConfigNodes->getLength() == 0) {
    
    xercesc::DOMElement *configElement = newEngineConfig->document->createElement(XERCESTRANSCODE("PlatformConfig"));
    configElement = (xercesc::DOMElement *)
      newEngineConfig->document->getDocumentElement()->insertBefore(configElement, NULL);
    
    newEngineConfig->platformConfig = PLATFORM->LoadConfig(configElement);

  }
  else 
    newEngineConfig->platformConfig = PLATFORM->LoadConfig((xercesc::DOMElement *)platformConfigNodes->item(0));
 
  xercesc::DOMNodeList *addinNodes = newEngineConfig->document->getElementsByTagName(XERCESTRANSCODE("Addin"));
  for (int i=0; i<addinNodes->getLength(); i++)
    newEngineConfig->addins.push_back(AddinConfig::Load((xercesc::DOMElement *)addinNodes->item(i)));

  return newEngineConfig;

}

PlatformConfig *EngineConfig::GetPlatformConfig() { return platformConfig; }
int EngineConfig::GetNumAddins() { return addins.size(); }
AddinConfig *EngineConfig::GetAddin(int index) { return addins[index]; }

AddinConfig *AddinConfig::Load(xercesc::DOMElement *element) {

  AddinConfig *ret = new AddinConfig();

  ret->source = XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("source"))); 
  
  return ret;

}

const char *AddinConfig::GetSource() { return this->source; }

