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

  InfoBase::Load(addin, docElement);

  addin->filename = &filename;
  addin->libraryFilename = new string(docElement.attribute("library").value());

  xml_node componentNode = doc->document_element.child("EngineComponent");

  if (componentNode)
    addin->type = ENGINE_COMPONENT_ADDIN;

  for (; componentNode; componentNode = componentNode.next_sibling("EngineComponent")) {
    EngineComponentInfo *componentInfo = EngineComponentInfo::Load(componentNode);
    addin->engineComponents.insert(EngineComponentInfoPair(componentInfo->GetName(), componentInfo));
  }     

  delete doc;

  return addin;

}

AddinType AddinInfo::GetType() { return this->type; }

const string &AddinInfo::GetLibraryFilename() { return *(this->libraryFilename); }

const EngineComponentInfoMap & AddinInfo::GetEngineComponents() { return this->engineComponents; }

AddinInfo::~AddinInfo() {
    
    delete libraryFilename;
    for (EngineComponentInfoMapIter iter = engineComponents.begin(); iter != engineComponents.end(); ++iter)
        delete (*iter).second;

}

EngineComponentInfo *EngineComponentInfo::Load(pugi::xml_node &element) {

  EngineComponentInfo *componentInfo = new EngineComponentInfo();
  InfoBase::Load(element);
  return componentInfo;
    
}

EngineComponentInfo::~EngineComponentInfo() {}

