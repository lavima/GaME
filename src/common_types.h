/*
File: CommonTypes.h
Author: Lars Vidar Magnusson
*/

#pragma once

template<typename K,typename V>
using unordered_dereferenced_pointer_map = std::unordered_map<K,V,PointerDereferenceHash<K>,PointerDereferenceEqualTo<K>>;
