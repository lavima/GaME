/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

using namespace pugi;

template<typename T> static T *InfoBase::Load(T *info, xml_node &xmlElement) {
    static_assert(std::is_base_of<InfoBase, T>::value, "T must derive from InfoBase");

    InfoBase *base = (InfoBase *)info;

    base->name = new string(docElement.child("Name").value()); 
    base->description = new string(docElement.child("Description").value()); 
    base->version = Version::Load(docElement.child("Version"));

    return info;

}

const string &InfoBase::GetName() { return *(this->name); }
const string &InfoBase::GetDescription() { return *(this->description); }
const string &InfoBase::GetVersion() { return *(this->version); }
