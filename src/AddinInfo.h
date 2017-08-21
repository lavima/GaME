/*
File: AddinInfo.h
Author: Lars Vidar Magnusson
*/

#ifndef __ADDININFO__
#define __ADDININFO__

enum AddinType {
  ENGINE_COMPONENT_ADDIN = 1
};

class EngineComponentInfo;

typedef std::unordered_map<const char *, EngineComponentInfo *, CStringHash, CStringCompare> EngineComponentInfoMap;
typedef std::pair<const char *, EngineComponentInfo *> EngineComponentInfoPair;
typedef EngineComponentInfoMap::iterator EngineComponentInfoMapIter;

class AddinInfo {

private:

  AddinType type;
  const char *name;
  const char *libraryFilename;

  EngineComponentInfoMap engineComponents;

  AddinInfo() {}

public:

  static AddinInfo *Load(const char *filename);

  EngineComponentInfo *GetEngineComponentInfo(const char *name);
  EngineComponentInfoMapIter GetEngineComponentInfoBegin();
  EngineComponentInfoMapIter GetEngineComponentInfoEnd();

  AddinType GetType();
  const char *GetName();
  const char *GetLibraryFilename();

};

class EngineComponentInfo {

private:

  const char *name;

  EngineComponentInfo() {}

public:

  static EngineComponentInfo *Load(xercesc::DOMElement *element); 

  const char *GetName();

};

#endif 
