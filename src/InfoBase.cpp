/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

template<typename T> static T *_InfoBase::Load(T *info, xml_node &xmlElement) {
    static_assert(std::is_base_of<_InfoBase, T>::value, "T must derive from _InfoBase");

    _InfoBase *base = (_InfoBase *)info;

    base->name = new string(docElement.child("Name").value()); 
    base->description = new string(docElement.child("Description").value()); 
    base->version = Version::Load(docElement.child("Version"));

    return info;

}

template<typename T> static T *_InfoBase::Create(T *info, const string *name, const string *description, const Version *version) {

   _InfoBase *base = (_InfoBase *)info;

   base->name = name;
   base->description = description;
   base->version = version;

   return info;

}

_InfoBase::~_InfoBase() {

    delete name;
    delete description;
    delete version;

}

const string &_InfoBase::GetName() { return *(this->name); }
const string &_InfoBase::GetDescription() { return *(this->description); }
const Version &_InfoBase::GetVersion() { return *(this->version); }
