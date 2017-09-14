/*
File: AddinContainer.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

AddinContainer *AddinContainer::Create(const string &filename) {

  AddinContainer *ret = new AddinContainer();

  ret->filename = &filename;
  ret->info = AddinInfo::Load(filename);

  return ret;

}

bool AddinContainer::HasSymbol(const string &name) { 
  return this->symbolMap.find(name) != this->symbolMap.end(); 
}

void AddinContainer::AddSymbol(const string &name, void *address) { 
  this->symbolMap.insert(SymbolMapPair(name, address)); 
}

void *AddinContainer::GetSymbol(const string &name) {

  if (this->HasSymbol(name))
    return this->symbolMap[name];

  return NULL;

}

const string &AddinContainer::GetFilename() { return *(this->filename); }
AddinInfo *AddinContainer::GetInfo() { return this->info; }
void *AddinContainer::GetHandle() { return this->handle; }
void AddinContainer::SetHandle(void *handle) { this->handle = handle; }
