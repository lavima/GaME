/*
File: AddinInfo.h
Author: Lars Vidar Magnusson
*/

#ifndef __ADDININFO__
#define __ADDININFO__

enum AddinType {
  GAME_COMPONENT_ADDIN = 1
};

class GameComponentInfo;

typedef std::unordered_map<const char *, GameComponentInfo *, CStringHash, CStringCompare> GameComponentInfoMap;
typedef std::pair<const char *, GameComponentInfo *> GameComponentInfoPair;
typedef GameComponentInfoMap::iterator GameComponentInfoMapIter;

class AddinInfo {

private:

  AddinType type;
  const char *name;
  const char *libraryFilename;

  GameComponentInfoMap gameComponents;

  AddinInfo() {}

public:

  static AddinInfo *Load(const char *filename);

  GameComponentInfo *GetGameComponentInfo(const char *name);
  GameComponentInfoMapIter GetGameComponentInfoBegin();
  GameComponentInfoMapIter GetGameComponentInfoEnd();

  AddinType GetType();
  const char *GetName();
  const char *GetLibraryFilename();

};

class GameComponentInfo {

private:

  const char *name;

  GameComponentInfo() {}

public:

  static GameComponentInfo *Load(xercesc::DOMElement *element); 

  const char *GetName();

};

#endif 
