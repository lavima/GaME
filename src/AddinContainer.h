/*
File: AddinContainer.h
Author: Lars Vidar Magnusson
*/

#pragma once

typedef std::unordered_map<string, void *> SymbolMap;
typedef std::pair<string, void *> SymbolMapPair;

struct AddinContainer {
  
private:

  const string *filename;
  AddinInfo *info;
  void *handle;

  SymbolMap symbolMap;

  AddinContainer() {}

public:
  
  static AddinContainer *Create(const string &filename);

  bool HasSymbol(const string &name);
  void AddSymbol(const string &name, void *address);
  void *GetSymbol(const string &name);

  const string &GetFilename();
  AddinInfo &GetInfo();
  void *GetHandle();
  void SetHandle(void *handle);
    
};