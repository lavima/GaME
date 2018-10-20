/*
File: Game.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

Game *Game::Load(const string &filename) {

  //printf("Loading game from %s\n", filename);

  xercesc::DOMDocument *document = Xerces::ParseDocument(filename);

  Game *ret = new Game(); 

  xercesc::DOMNodeList *infoNodes = document->getDocumentElement()->getElementsByTagName(XERCESTRANSCODE("Info"));
  xercesc::DOMElement *infoElement = (xercesc::DOMElement *)infoNodes->item(0);

  xercesc::DOMElement *nameElement = (xercesc::DOMElement *)infoElement->getElementsByTagName(XERCESTRANSCODE("Name"))->item(0);
  unique_ptr<const string> namePtr(Xerces::GetElementText(nameElement));
  ret->info.Name.assign(*namePtr);

  xercesc::DOMNode *majorVersionNode = infoElement->getElementsByTagName(XERCESTRANSCODE("MajorVersion"))->item(0);
  ret->info.MajorVersion = atoi(XERCESTRANSCODE(majorVersionNode->getNodeValue()));
  xercesc::DOMNode *minorVersionNode = infoElement->getElementsByTagName(XERCESTRANSCODE("MinorVersion"))->item(0);
  ret->info.MinorVersion = atoi(XERCESTRANSCODE(minorVersionNode->getNodeValue()));
  xercesc::DOMNode *releaseNode = infoElement->getElementsByTagName(XERCESTRANSCODE("Release"))->item(0);
  ret->info.Release = atoi(XERCESTRANSCODE(releaseNode->getNodeValue()));

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

const GameInfo &Game::GetInfo() { return info; }