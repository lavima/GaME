/*
File: InfoBase.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

template<typename T> static T *InfoBase::Load(T *info, const string &filename) {
    static_assert(std::is_base_of<InfoBase, T>::value, "T must derive from InfoBase");
    ret->name = new string(docElement.attribute("name").value()); 
}

const string &InfoBase::GetName() { return *(this->name); }
const string &InfoBase::GetDescription() { return *(this->description); }
const string &InfoBase::GetVersion() { return *(this->version); }
