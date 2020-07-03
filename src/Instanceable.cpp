/*
File: Instanceable.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


uint64_t Instanceable::instance_counter_;
unordered_map<uint_fast64_t, string> Instanceable::hash_typename_;


Instanceable::Instanceable(const string &typeName) {
    
    this->instance_id_ = Instanceable::instance_counter_++;

    uint_fast64_t type_hash = hash<string>{}(typeName);
    this->type_hash_ = type_hash;
    if (Instanceable::hash_typename_.find(type_hash) == Instanceable::hash_typename_.end())
        Instanceable::hash_typename_[type_hash] = typeName;

}

const string& Instanceable::GetTypeName() const { return Instanceable::hash_typename_[type_hash_]; }

bool Instanceable::operator==(const Instanceable&other) { return this->instance_id_ == other.instance_id_; }
