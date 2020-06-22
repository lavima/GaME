/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

__InfoBase::__InfoBase(const string &name, const string &description, const Version &version) {

    this->name = name;
    this->description = description;
    this->version = version;

}

__InfoBase::__InfoBase(const string &&name, const string &&description, const Version &&version) {

    this->name = name;
    this->description = description;
    this->version = version;

}

__InfoBase::__InfoBase(pugi::xml_node xmlNode) { assert(this->Load(xmlNode)); }

bool __InfoBase::Load(__InfoBase *info, pugi::xml_node rootNode) {

    xml_node nameNode = rootNode.child(XMLNAME_INFOBASE_NAME);
    if (!nameNode)
        return false;
    info->name = string(nameNode.value());

    xml_node descriptionNode = rootNode.child(XMLNAME_INFOBASE_DESCRIPTION);
    if (!descriptionNode)
        return false;
    info->description = string(descriptionNode.value());

    return info->version.Load(rootNode.child(XMLNAME_INFOBASE_VERSION));

}

bool __InfoBase::Save(__InfoBase &info, pugi::xml_node rootNode) {

    xml_node nameNode = rootNode.append_child(XMLNAME_INFOBASE_NAME);
    nameNode.set_value(info.name.c_str());

    xml_node descriptionNode = rootNode.append_child(XMLNAME_INFOBASE_DESCRIPTION);
    descriptionNode.set_value(info.description.c_str());

    xml_node versionNode = rootNode.append_child();
    return info.version.Save(versionNode);

}

void __InfoBase::SetName(const string &name) { this->name = name; }
void __InfoBase::SetDescription(const string &description) { this->description = description; }
void __InfoBase::SetVersion(const Version &version) { this->version = version; }

bool __InfoBase::Load(pugi::xml_node rootNode) { return __InfoBase::Load(this, rootNode); }
bool __InfoBase::Save(pugi::xml_node rootNode) { return __InfoBase::Save(*this, rootNode); }

const string &__InfoBase::GetName() const { return name; }
const string &__InfoBase::GetDescription() const { return description; }
const Version &__InfoBase::GetVersion() const { return this->version; }

