/*
File: Game.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

Game *Game::Load(const string &filename) {

  //printf("Loading game from %s\n", filename);

  xercesc::DOMDocument *document = XercesParseDocument(filename);

  Game *ret = new Game();

  ret->name = new string(XERCESTRANSCODE(document->getDocumentElement()->getAttribute(XERCESTRANSCODE("name")))); 

  xercesc::DOMNodeList *componentNodes = document->getElementsByTagName(XERCESTRANSCODE("EngineComponent"));
  for (int i=0; i<componentNodes->getLength(); i++) {
    xercesc::DOMElement *componentElement = (xercesc::DOMElement *)componentNodes->item(i);
    ret->engineComponentsNeeded.insert(
      EngineComponentsNeededMapPair(
        string(XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("type")))), 
        string(XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("name"))))));
  }

  return ret;

}

void Game::Initialize() {
  
}

void Game::LoadContent() {

}

void Game::UnloadContent() {

}

void Game::Update(GameTime &gameTime) {

}

const string &Game::GetName() { return *(this->name); }