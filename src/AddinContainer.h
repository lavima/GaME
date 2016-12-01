/*
File: AddinContainer.h
Author: Lars Vidar Magnusson
*/

#ifndef __ADDINCONTAINER__
#define __ADDINCONTAINER__

typedef std::unordered_map<const char *, void *, CStringHash, CStringCompare> SymbolMap;
typedef std::pair<const char *, void *> SymbolMapPair;

struct AddinContainer {
  
private:

  const char *filename;
  AddinInfo *info;
  void *handle;

  SymbolMap symbolMap;

  AddinContainer() {}

public:
  
  static AddinContainer *Create(const char *filename);

  bool HasSymbol(const char *name);
  void AddSymbol(const char *name, void *address);
  void *GetSymbol(const char *name);

  const char *GetFilename();
  AddinInfo *GetInfo();
  void *GetHandle();
  void SetHandle(void *handle);

};

#endif
