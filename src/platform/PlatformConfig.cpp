/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include "../lib/Xerces.h"
#include "PlatformConfig.h"
#include "Platform.h"
#ifdef OS_WIN
#include "Win32Vulkan.h"
#endif // OS_WIN


PlatformConfig::PlatformConfig() {

#ifdef OS_WIN
    this->typeName = TYPENAME_WIN32VULKAN;
#endif // OS_WIN

}

PlatformConfig::PlatformConfig(const string &typeName) { 
    
    this->typeName = typeName; 

}

const string &PlatformConfig::GetTypeName() { return typeName; }
void PlatformConfig::SetTypeName(const string &typeName) { this->typeName = typeName; }

PlatformConfig *PlatformConfig::Load(xercesc::DOMDocument *document) {

    xercesc::DOMNodeList *platformConfigNodes =
        document->getElementsByTagName(XERCESTRANSCODE("GraphicalPlatformConfig"));
    if (platformConfigNodes->getLength())
        return GraphicalPlatformConfig::Load((xercesc::DOMElement *)platformConfigNodes->item(0));

    return new PlatformConfig("Undecided");
}


GraphicalPlatformConfig::GraphicalPlatformConfig() {

    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->fullscreen = DEFAULT_FULLSCREEN;

}

GraphicalPlatformConfig::GraphicalPlatformConfig(const string &typeName, int width, int height, bool fullscreen) 
    : PlatformConfig(typeName) {

    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;

}

GraphicalPlatformConfig *GraphicalPlatformConfig::Load(xercesc::DOMElement *element) {   
    

    GraphicalPlatformConfig *newConfig = new GraphicalPlatformConfig();

    newConfig->typeName = string(XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("type"))));

    xercesc::DOMNodeList *widthElements = element->getElementsByTagName(XERCESTRANSCODE("Width"));
    if (widthElements->getLength() != 0)
        newConfig->width = xercesc::XMLString::parseInt(widthElements->item(0)->getFirstChild()->getNodeValue());

    xercesc::DOMNodeList *heightElements = element->getElementsByTagName(XERCESTRANSCODE("Height"));
    if (heightElements->getLength() != 0)
        newConfig->height = xercesc::XMLString::parseInt(heightElements->item(0)->getFirstChild()->getNodeValue());

    xercesc::DOMNodeList *fullscreenElements = element->getElementsByTagName(XERCESTRANSCODE("Fullscreen"));
    if (fullscreenElements->getLength() != 0) {

        xercesc::DOMNode *textNode = fullscreenElements->item(0)->getFirstChild();

        if (xercesc::XMLString::equals(textNode->getNodeValue(), XERCESTRANSCODE("true")))
            newConfig->fullscreen = true;
        else if (xercesc::XMLString::equals(textNode->getNodeValue(), XERCESTRANSCODE("false")))
            newConfig->fullscreen = false;

    }

    return newConfig;

}

int GraphicalPlatformConfig::GetWidth() { return this->width; }
void GraphicalPlatformConfig::SetWidth(int width) { this->width = width; }

int GraphicalPlatformConfig::GetHeight() { return this->height; }
void GraphicalPlatformConfig::SetHeight(int width) { this->height = height; }

bool GraphicalPlatformConfig::GetFullscreen() { return this->fullscreen; }
void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }