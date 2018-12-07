/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

_InfoBase::_InfoBase(const string &name, const string &description, const Version &version) {

    this->name = name;
    this->description = description;
    this->version = version;

}

_InfoBase::_InfoBase(const string &&name, const string &&description, const Version &&version) {

    this->name = name;
    this->description = description;
    this->version = version;

}

_InfoBase::_InfoBase(pugi::xml_node &xmlNode) {

    this->name = xmlNode.child("Name").value();
    this->description = string(xmlNode.child("Description").value());
    this->version = Version(xmlNode.child("Version"));

}

_InfoBase::_InfoBase(pugi::xml_node &&xmlNode) {

    this->name = xmlNode.child("Name").value();
    this->description = string(xmlNode.child("Description").value());
    this->version = Version(xmlNode.child("Version"));

}

_InfoBase::~_InfoBase() {

}

const string &_InfoBase::GetName() { return name; }
const string &_InfoBase::GetDescription() { return description; }
const Version &_InfoBase::GetVersion() { return this->version; }

