/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

AddinInfo *AddinInfo::Load(const string &filename) {

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  AddinInfo *ret = new AddinInfo();

  ret->name = new string(XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name")))); 
  ret->libraryFilename = new string(XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("library"))));

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

EngineComponentInfo *AddinInfo::GetEngineComponentInfo(const string &name) {

  EngineComponentInfoMapIter item = engineComponents.find(name);
  if (item == engineComponents.end())
    return NULL;
  return item->second;

}

EngineComponentInfoMapIter AddinInfo::GetEngineComponentInfoBegin() { return engineComponents.begin(); }
EngineComponentInfoMapIter AddinInfo::GetEngineComponentInfoEnd() { return engineComponents.end(); }

AddinType AddinInfo::GetType() { return this->type; }
const string &AddinInfo::GetName() { return *(this->name); }
const string &AddinInfo::GetLibraryFilename() { return *(this->libraryFilename); }


EngineComponentInfo *EngineComponentInfo::Load(xercesc::DOMElement *element) {

  EngineComponentInfo *ret = new EngineComponentInfo();
  ret->name = new string(XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("name")))); 
  return ret;

}

const string &EngineComponentInfo::GetName() { return *(this->name); }
