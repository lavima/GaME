/*
File: AddinInfo.cpp
Author: Lars Vidar Magnusson
*/

#include <stdlib.h>
#include <string.h>

#include <utility>
#include <vector>
#include <unordered_map>

#include <xercesc/dom/DOM.hpp>

#include "lib/XercesUtils.h"
#include "lib/CStringHash.h"
#include "AddinInfo.h"

AddinInfo *AddinInfo::Load(const char *filename) {

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  AddinInfo *ret = new AddinInfo();

  ret->name = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name"))); 
  ret->libraryFilename = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("library")));

  xercesc::DOMNodeList *gameComponentElements = document->getElementsByTagName(XERCESTRANSCODE("GameComponent"));
  if (gameComponentElements->getLength() > 0)
    ret->type = GAME_COMPONENT_ADDIN;
  for (int i=0; i<gameComponentElements->getLength(); i++) {
   
    GameComponentInfo *componentInfo = GameComponentInfo::Load((xercesc::DOMElement *)gameComponentElements->item(i));
    ret->gameComponents.insert(GameComponentInfoPair(componentInfo->GetName(), componentInfo));

  }     

  document->release();

  return ret;

}

GameComponentInfo *AddinInfo::GetGameComponentInfo(const char *name) {

  GameComponentInfoMapIter item = gameComponents.find(name);
  if (item == gameComponents.end())
    return NULL;
  return item->second;

}

GameComponentInfoMapIter AddinInfo::GetGameComponentInfoBegin() { return gameComponents.begin(); }
GameComponentInfoMapIter AddinInfo::GetGameComponentInfoEnd() { return gameComponents.end(); }

AddinType AddinInfo::GetType() { return this->type; }
const char *AddinInfo::GetName() { return this->name; }
const char *AddinInfo::GetLibraryFilename() { return this->libraryFilename; }


GameComponentInfo *GameComponentInfo::Load(xercesc::DOMElement *element) {

  GameComponentInfo *ret = new GameComponentInfo();
  ret->name = XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("name"))); 
  return ret;

}

const char *GameComponentInfo::GetName() { return this->name; }
