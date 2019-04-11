/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

Addin *Addin::Load(const string &filename) {

  Addin *ret = new Addin();
  ret->filename = &filename;
  
  xml_document *document = PugiXML::ParseDocument(filename);
  
  ret->info = new AddinInfo(*document);

  return ret;

}

bool Addin::HasSymbol(const string &name) { 
  return this->symbolMap.find(name) != this->symbolMap.end(); 
}

void Addin::AddSymbol(const string &name, void *address) { 
  this->symbolMap.insert(SymbolMapPair(name, address)); 
}

void *Addin::GetSymbol(const string &name) {

  if (this->HasSymbol(name))
    return this->symbolMap[name];

  return NULL;

}

const string &Addin::GetFilename() { return *(this->filename); }
AddinInfo &Addin::GetInfo() { return *(this->info); }
void *Addin::GetHandle() { return this->handle; }
void Addin::SetHandle(void *handle) { this->handle = handle; }

