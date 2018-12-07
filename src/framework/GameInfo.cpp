/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

GameInfo::GameInfo(xml_node &xmlNode) : _InfoBase(xmlNode) {
    
    xml_node addinNode = xmlNode.child("Addin");
    for ( ; addinNode; addinNode = addinNode.next_sibling("Addin"))
        this->requiredAddins.push_back(string(addinNode.value()));

}

GameInfo::~GameInfo() {}

const vector<string> &GameInfo::GetRequiredAddins() const { return requiredAddins; }
