/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"


PlatformConfig::PlatformConfig() {

#ifdef OS_WIN
    this->name = TYPENAME_WIN32VULKAN;
#endif // OS_WIN

}

PlatformConfig::PlatformConfig(const string &name) { 
    
    this->name = name; 

}

const string &PlatformConfig::GetTypeName() { return name; }
void PlatformConfig::SetTypeName(const string &name) { this->name = name; }

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

GraphicalPlatformConfig::GraphicalPlatformConfig(const string &name, int width, int height, bool fullscreen) 
    : PlatformConfig(name) {

    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;

}

GraphicalPlatformConfig *GraphicalPlatformConfig::Load(xercesc::DOMElement *element) {   
    

    GraphicalPlatformConfig *newConfig = new GraphicalPlatformConfig();

    newConfig->name = string(XERCESTRANSCODE(element->getAttribute(XERCESTRANSCODE("type"))));

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