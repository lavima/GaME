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

#include "../lib/CStringHash.h"
#include "../lib/XercesUtils.h"
#include "../scripting/ScriptContext.h"
#include "../scripting/Script.h"
#include "GameTime.h"
#include "GameComponent.h"
#include "Game.h"
#include "../platform/PlatformConfig.h"
#include "../platform/Platform.h"
#include "../AddinInfo.h"
#include "../AddinContainer.h"
#include "../Addin.h"
#include "../EngineConfig.h"
#include "../Engine.h"

Game *Game::Load(const char *filename) {

  printf("Loading game from %s\n", filename);

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  Game *ret = new Game();

  ret->name = XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name"))); 

  xercesc::DOMNodeList *componentNodes = document->getElementsByTagName(XERCESTRANSCODE("GameComponent"));
  for (int i=0; i<componentNodes->getLength(); i++) {
    xercesc::DOMElement *componentElement = (xercesc::DOMElement *)componentNodes->item(i);
    ret->AddComponent(XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("type"))), 
      XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("name"))));
  }

  return ret;

}

void Game::Initialize() {
  
  for (GameComponentMapIter iter=components.begin(); iter!=components.end(); ++iter)
    iter->second->Initialize();

}

void Game::LoadContent() {

}

void Game::Update(GameTime *gameTime) {

  for (GameComponentMapIter iter=components.begin(); iter!=components.end(); ++iter)
    iter->second->Update(gameTime);

}

const char *Game::GetName() { return this->name; }

void Game::AddComponent(const char *typeName, const char *name) {

  if (components.find(name) != components.end())
    printf("The component with the specified name (%s) already exists\n", name);

  components[name] = GameComponent::Create(this, typeName, name);
  
}

void Game::AddComponent(GameComponent *component) {
  
  if (components.find(component->GetName()) != components.end())
    printf("The component with the specified name (%s) already exists\n", name);

  components[name] = component;

}

GameComponent *Game::GetComponent(const char *name) { 

  if (this->components.find(name) == this->components.end())
    return NULL;
  return this->components[name];

}
