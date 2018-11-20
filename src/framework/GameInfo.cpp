/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

GameInfo::~GameInfo() {
    
    for (vector<const char *> iter = engineComponents.begin(); iter != engineComponents.end(); ++iter)
        delete (*iter);

}

GameInfo *GameInfo::Load(const string &filename) {
    
    xml_document *document = PugiXML::ParseDocument(filename);

    GameInfo *info = new GameInfo();
    info->filename = new string(filename);

    xml_node rootElement = document->document_element();

    _InfoBase::Load(info, rootElement);

    xml_node componentNode = document->child("EngineComponent");
    for ( ; componentNode; componentNode = componentNode.next_sibling("EngineComponent"))
        ret->engineComponents.push_back(new string(componentNode.value()));

    return ret;
}

const string &GameInfo::GetName() const { return *name; }
const string &GameInfo::GetDescription() const { return *description; }
const Version &GameInfo::GetVersion() const { return *version; }
const EngineComponentNameMap &GameInfo::GetEngineComponents() const { return engineComponents; }
