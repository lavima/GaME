/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

AddinInfo::AddinInfo(xml_document &xmlDocument) : _InfoBase(xmlDocument.document_element()) {

    xml_node docElement = xmlDocument.document_element();

    this->filename = filename;
    this->libraryFilename = string(docElement.attribute("library").value());

    xml_node componentNode = docElement.child("EngineComponent");

    if (componentNode)
        this->type = ENGINE_COMPONENT_ADDIN;

    for (; componentNode; componentNode = componentNode.next_sibling("EngineComponent")) {
        EngineComponentInfo *componentInfo = new EngineComponentInfo(componentNode);
        this->engineComponents.insert(pair<string, EngineComponentInfo *>(componentInfo->GetName(), componentInfo));
    }

}

AddinType AddinInfo::GetType() { return this->type; }

const string &AddinInfo::GetLibraryFilename() { return this->libraryFilename; }

const unordered_map<string, EngineComponentInfo *> &AddinInfo::GetEngineComponents() const { return this->engineComponents; }

AddinInfo::~AddinInfo() {

    for (unordered_map<string, EngineComponentInfo *>::iterator iter = engineComponents.begin(); iter != engineComponents.end(); ++iter)
        delete (*iter).second;

}

EngineComponentInfo::EngineComponentInfo(pugi::xml_node &xmlNode) : _InfoBase(xmlNode) {}

EngineComponentInfo::~EngineComponentInfo() {}

