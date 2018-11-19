/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

template<typename T> static T *_InfoBase::Create(T *info, const string *name, const string *description, const Version *version) {
    static_assert(std::is_base_of<_InfoBase, T>::value, "T must derive from _InfoBase");

   _InfoBase *base = (_InfoBase *)info;

   base->name = name;
   base->description = description;
   base->version = version;

   return info;

}

_InfoBase::_InfoBase(const string *name, const string *description, const Version *version) {
    
   this->name = name;
   this->description = description;
   this->version = version;

}

_InfoBase::~_InfoBase() {

    delete name;
    delete description;
    delete version;

}

const string &_InfoBase::GetName() { return *(this->name); }
const string &_InfoBase::GetDescription() { return *(this->description); }
const Version &_InfoBase::GetVersion() { return *(this->version); }

template<typename T> static T *_InfoBaseXML::Load(T *info, xml_node &xmlElement) {

     T ret = _InfoBase::Create(info,
         new string(docElement.child("Name").value()), 
         new string(docElement.child("Description").value()),
         Version::Load(docElement.child("Version")));

    return ret;

}

