/*
File: Win32Config.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>

#include <xercesc/dom/DOM.hpp>

#include "../../lib/Xerces.h"
#include "../PlatformConfig.h"
#include "Win32Config.h"

Win32Config *Win32Config::Load(xercesc::DOMElement *element) {

	const char * typeName = XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("type")));
	if (strcmp(typeName, "Win32") != 0) {
		printf("ERROR: Wrong platform configuration type.\n");
		return NULL;
	}


	Win32Config *newConfig = new Win32Config();

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

int Win32Config::GetWidth() { return this->width; }
int Win32Config::GetHeight() { return this->height; }

bool Win32Config::GetFullscreen() { return this->fullscreen; }
void Win32Config::SetFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
}
