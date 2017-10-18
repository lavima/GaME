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

AddinType AddinInfo::GetType() { return this->type; }
const string &AddinInfo::GetName() { return *(this->name); }
const string &AddinInfo::GetDescription() { return *(this->description); }
const string &AddinInfo::GetVersion() { return *(this->version); }
const string &AddinInfo::GetLibraryFilename() { return *(this->libraryFilename); }
const EngineComponentInfoMap & AddinInfo::GetEngineComponents() { return this->engineComponents; }


EngineComponentInfo *EngineComponentInfo::Load(xercesc::DOMElement *element) {

  EngineComponentInfo *ret = new EngineComponentInfo();
  ret->name = new string(XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("name")))); 
  return ret;

}

const string &EngineComponentInfo::GetName() { return *(this->name); }
const string & EngineComponentInfo::GetDescription() { return *(this->description); }
const string & EngineComponentInfo::GetVersion() { return *(this->version); }
