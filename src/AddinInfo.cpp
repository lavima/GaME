/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace xercesc;

AddinInfo *AddinInfo::Load(const string &filename) {

  xercesc::DOMDocument *document = Xerces::ParseDocument(filename);

  AddinInfo *addin = new AddinInfo();
  addin->filename = &filename;

  DOMElement *rootElement = (DOMElement *)document->getDocumentElement();

  DOMElement *nameElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Name"))->item(0);
  addin->name = Xerces::GetElementText(nameElement);
  DOMElement *descriptionElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Description"))->item(0);
  addin->description = Xerces::GetElementText(descriptionElement);

  addin->version = Version::Load((DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Version"))->item(0));

  DOMElement *libraryElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("LibraryFilename"))->item(0);
  addin->libraryFilename = Xerces::GetElementText(libraryElement);

  xercesc::DOMNodeList *engineComponentElements = document->getElementsByTagName(XERCESTRANSCODE("EngineComponent"));

  if (engineComponentElements->getLength() > 0)
      addin->addinType = ENGINE_COMPONENT_ADDIN;

  for (int i=0; i<engineComponentElements->getLength(); i++) {

    EngineComponentInfo *componentInfo = new EngineComponentInfo();
    
    DOMElement *typeNameElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Name"))->item(0);
    componentInfo->typeName = Xerces::GetElementText(typeNameElement);
    DOMElement *componentDescriptionElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Description"))->item(0);
    componentInfo->description = Xerces::GetElementText(componentDescriptionElement);
    componentInfo->version = Version::Load((DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Version"))->item(0));

    addin->engineComponents.insert(EngineComponentInfoPair(componentInfo->GetTypeName(), componentInfo));

  }     

  document->release();

  return addin;

}

AddinType AddinInfo::GetType() { return this->addinType; }

const string &AddinInfo::GetName() { return *(this->name); }
const string &AddinInfo::GetDescription() { return *(this->description); }

const Version &AddinInfo::GetVersion() { return *(this->version); }

const string &AddinInfo::GetFilename() { return *(this->filename); }
const string &AddinInfo::GetLibraryFilename() { return *(this->libraryFilename); }

const EngineComponentInfoMap & AddinInfo::GetEngineComponents() { return this->engineComponents; }

AddinInfo::~AddinInfo() {
    
    delete name;
    delete description;
    delete version;
    delete libraryFilename;

    for (EngineComponentInfoMapIter iter = engineComponents.begin(); iter != engineComponents.end(); ++iter)
        delete (*iter).second;
    
}

EngineComponentInfo::~EngineComponentInfo() {
    
    delete typeName;
    delete description;
    delete version;

}

const string &EngineComponentInfo::GetTypeName() { return *typeName; }
const string &EngineComponentInfo::GetDescription() { return *description; }
const Version &EngineComponentInfo::GetVersion() { return *version; }