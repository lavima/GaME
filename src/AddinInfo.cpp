/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include <stdlib.h>
#include <string.h>

#include <utility>
#include <vector>
#include <unordered_map>

#include <xercesc/dom/DOM.hpp>

#include "lib/Xerces.h"
#include "lib/CStringHash.h"
#include "AddinInfo.h"

AddinInfo *AddinInfo::Load(const char *filename) {

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  AddinInfo *ret = new AddinInfo();

  ret->name = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name"))); 
  ret->libraryFilename = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("library")));

  xercesc::DOMNodeList *engineComponentElements = document->getElementsByTagName(XERCESTRANSCODE("EngineComponent"));

  if (engineComponentElements->getLength() > 0)
    ret->type = ENGINE_COMPONENT_ADDIN;

  for (int i=0; i<engineComponentElements->getLength(); i++) {
    EngineComponentInfo *componentInfo = EngineComponentInfo::Load((xercesc::DOMElement *)engineComponentElements->item(i));
    ret->engineComponents.insert(EngineComponentInfoPair(componentInfo->GetName(), componentInfo));
  }     

  document->release();

  return ret;

}

EngineComponentInfo *AddinInfo::GetEngineComponentInfo(const char *name) {

  EngineComponentInfoMapIter item = engineComponents.find(name);
  if (item == engineComponents.end())
    return NULL;
  return item->second;

}

EngineComponentInfoMapIter AddinInfo::GetEngineComponentInfoBegin() { return engineComponents.begin(); }
EngineComponentInfoMapIter AddinInfo::GetEngineComponentInfoEnd() { return engineComponents.end(); }

AddinType AddinInfo::GetType() { return this->type; }
const char *AddinInfo::GetName() { return this->name; }
const char *AddinInfo::GetLibraryFilename() { return this->libraryFilename; }


EngineComponentInfo *EngineComponentInfo::Load(xercesc::DOMElement *element) {

  EngineComponentInfo *ret = new EngineComponentInfo();
  ret->name = XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("name"))); 
  return ret;

}

const char *EngineComponentInfo::GetName() { return this->name; }
