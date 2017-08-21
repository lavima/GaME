/*
File: Game.cpp
Author: Lars Vidar Magnusson
*/

#include <assert.h>
#include <stdio.h>

#include <vector>
#include <unordered_map>

#include <v8.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>

#include "../lib/CommonTypes.h"
#include "../lib/CStringHash.h"
#include "../lib/Xerces.h"
#include "../scripting/ScriptEnvironment.h"
#include "../scripting/Script.h"
#include "GameTime.h"
#include "Game.h"
#include "../platform/PlatformConfig.h"
#include "../platform/Platform.h"
#include "../AddinInfo.h"
#include "../AddinContainer.h"
#include "../Addin.h"
#include "../EngineConfig.h"
#include "../EngineComponent.h"
#include "../Engine.h"

Game *Game::Load(const char *filename) {

  printf("Loading game from %s\n", filename);

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  Game *ret = new Game();

  ret->name = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name"))); 

  xercesc::DOMNodeList *componentNodes = document->getElementsByTagName(XERCESTRANSCODE("EngineComponent"));
  for (int i=0; i<componentNodes->getLength(); i++) {
    xercesc::DOMElement *componentElement = (xercesc::DOMElement *)componentNodes->item(i);
    ret->engineComponentsNeeded.insert(
      EngineComponentsNeededMapPair(
        XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("type"))), 
        (const char *)XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("name")))));
  }

  return ret;

}

void Game::Initialize() {
  
}

void Game::LoadContent() {

}

void Game::Update(GameTime *gameTime) {

}

const char *Game::GetName() { return this->name; }