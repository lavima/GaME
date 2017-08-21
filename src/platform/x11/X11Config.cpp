/*
File: X11Config.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>

#include <xercesc/dom/DOM.hpp>

#include "../../lib/Xerces.h"
#include "../PlatformConfig.h"
#include "X11Config.h"

X11Config *X11Config::Load(xercesc::DOMElement *element) {

  const char * typeName = XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("type")));
  if (strcmp(typeName, "X11") != 0) {
    printf("ERROR: Wrong platform configuration type.\n");
    return NULL;
  }

  
  X11Config *newConfig = new X11Config();

  xercesc::DOMNodeList *widthElements = element->getElementsByTagName(XERCESTRANSCODE("Width"));
  if (widthElements->getLength() == 0)
    newConfig->width = DEFAULT_WIDTH;
  else
    newConfig->width = xercesc::XMLString::parseInt(widthElements->item(0)->getFirstChild()->getNodeValue());

  xercesc::DOMNodeList *heightElements = element->getElementsByTagName(XERCESTRANSCODE("Height"));
  if (heightElements->getLength() == 0)
    newConfig->height = DEFAULT_HEIGHT;
  else
    newConfig->height = xercesc::XMLString::parseInt(heightElements->item(0)->getFirstChild()->getNodeValue());

  xercesc::DOMNodeList *fullscreenElements = element->getElementsByTagName(XERCESTRANSCODE("Fullscreen"));
  if (fullscreenElements->getLength() == 0)
    newConfig->fullscreen = DEFAULT_FULLSCREEN;
  else {

    xercesc::DOMNode *textNode = fullscreenElements->item(0)->getFirstChild();

    if (xercesc::XMLString::equals(textNode->getNodeValue(), XERCESTRANSCODE("true")))
      newConfig->fullscreen = true;
    else if (xercesc::XMLString::equals(textNode->getNodeValue(), XERCESTRANSCODE("false")))
      newConfig->fullscreen = false;
    else
      newConfig->fullscreen = DEFAULT_FULLSCREEN;

  }
  
}

int X11Config::GetWidth() { return this->width; }
int X11Config::GetHeight() { return this->height; }

bool X11Config::GetFullscreen() { return this->fullscreen; }
void X11Config::SetFullscreen(bool fullscreen) {
  this->fullscreen = fullscreen;
}
