/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

AddinInfo *AddinInfo::Load(const string &filename) {

  pugi::xml_document *doc = PugiXML::ParseDocument(filename);
  pugi::xml_node docElement = doc->document_element;

  AddinInfo *ret = new AddinInfo();

  ret->libraryFilename = new string(docElement.attribute("library").value());

  pugi::xml_node componentNode = doc-document_element.child("EngineComponent");

  if (componentNode)
    ret->type = ENGINE_COMPONENT_ADDIN;

  for (; componentNode; componentNode = componentNode.next_sibling("EngineComponent")) {
    EngineComponentInfo *componentInfo = EngineComponentInfo::Load(componentNode);
    ret->engineComponents.insert(EngineComponentInfoPair(componentInfo->GetName(), componentInfo));
  }     

  delete doc;

  return ret;

}

AddinType AddinInfo::GetType() { return this->type; }
const string &AddinInfo::GetLibraryFilename() { return *(this->libraryFilename); }
const EngineComponentInfoMap & AddinInfo::GetEngineComponents() { return this->engineComponents; }


EngineComponentInfo *EngineComponentInfo::Load(pugi::xml_node &element) {

  EngineComponentInfo *ret = new EngineComponentInfo();
  ret->name = new string(element.attribute("name").value()); 
  return ret;

}

const string &EngineComponentInfo::GetName() { return *(this->name); }
const string & EngineComponentInfo::GetDescription() { return *(this->description); }
const string & EngineComponentInfo::GetVersion() { return *(this->version); }
