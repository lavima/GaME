/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

using namespace pugi;

AddinInfo *AddinInfo::Load(const string &filename) {

  xml_document *doc = PugiXML::ParseDocument(filename);
  xml_node docElement = doc->document_element;

  AddinInfo *addin = new AddinInfo();
  addin->filename = &filename;

  DOMElement *rootElement = (DOMElement *)document->getDocumentElement();

  DOMElement *nameElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Name"))->item(0);
  addin->name = Xerces::GetElementText(nameElement);
  DOMElement *descriptionElement = (DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Description"))->item(0);
  addin->description = Xerces::GetElementText(descriptionElement);

  ret->libraryFilename = new string(docElement.attribute("library").value());

  pugi::xml_node componentNode = doc-document_element.child("EngineComponent");

  if (componentNode)
    ret->type = ENGINE_COMPONENT_ADDIN;

  for (; componentNode; componentNode = componentNode.next_sibling("EngineComponent")) {
    EngineComponentInfo *componentInfo = EngineComponentInfo::Load(componentNode);
    ret->engineComponents.insert(EngineComponentInfoPair(componentInfo->GetName(), componentInfo));
  }     

  delete doc;

  return addin;

}

AddinType AddinInfo::GetType() { return this->type; }

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

EngineComponentInfo *EngineComponentInfo::Load(pugi::xml_node &element) {

  EngineComponentInfo *ret = new EngineComponentInfo();
  ret->name = new string(element.attribute("name").value()); 
  return ret;
    
}

EngineComponentInfo::~EngineComponentInfo() {
    
    delete typeName;
    delete description;
    delete version;

}

const string &EngineComponentInfo::GetTypeName() { return *typeName; }
const string &EngineComponentInfo::GetDescription() { return *description; }
const Version &EngineComponentInfo::GetVersion() { return *version; }
