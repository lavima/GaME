/*
File: AddinContainer.cpp
Author: Lars Vidar Magnusson
*/

#include <stdlib.h>
#include <string.h>

#include <vector>
#include <unordered_map>

#include <xercesc/dom/DOM.hpp>

#include "lib/CStringHash.h"
#include "AddinInfo.h"
#include "AddinContainer.h"

AddinContainer *AddinContainer::Create(const char *filename) {

  AddinContainer *ret = new AddinContainer();

  ret->filename = filename;
  ret->info = AddinInfo::Load(filename);

  return ret;

}

bool AddinContainer::HasSymbol(const char *name) { 
  return this->symbolMap.find(name) != this->symbolMap.end(); 
}

void AddinContainer::AddSymbol(const char *name, void *address) { 
  this->symbolMap.insert(SymbolMapPair(name, address)); 
}

void *AddinContainer::GetSymbol(const char *name) {

  if (this->HasSymbol(name))
    return this->symbolMap[name];

  return NULL;

}

const char *AddinContainer::GetFilename() { return this->filename; }
AddinInfo *AddinContainer::GetInfo() { return this->info; }
void *AddinContainer::GetHandle() { return this->handle; }
void AddinContainer::SetHandle(void *handle) { this->handle = handle; }
