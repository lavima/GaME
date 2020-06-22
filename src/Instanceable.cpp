/*
File: Instanceable.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


uint64_t __Instanceable::instanceCounter;

__Instanceable::__Instanceable(const string &typeName) {
    
    this->instanceId = __Instanceable::instanceCounter++;

    this->typeName = typeName;
    this->typeHash = hash<string>{}(typeName);

}

const string &__Instanceable::GetTypeName() const { return typeName; }

bool __Instanceable::operator==(const __Instanceable &other) { return this->instanceId == other.instanceId; }
