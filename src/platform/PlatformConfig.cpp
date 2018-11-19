/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

PlatformConfig::PlatformConfig(const string &typeName) {

    this->typeName = new string(typeName);

}

const string &PlatformConfig::GetTypeName() { return typeName; }
void PlatformConfig::SetTypeName(const string &typeName) { this->typeName = typeName; }

PlatformConfig *PlatformConfig::Load(xml_document &xmlDocument) {

    xml_node graphicalConfig = xmlDocument.child("GraphicalPlatformConfig");
    if (platformConfig)
        return GraphicalPlatformConfig::Load(platformConfig);

    return new PlatformConfig("Undecided");

}


GraphicalPlatformConfig::GraphicalPlatformConfig() {

    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->fullscreen = DEFAULT_FULLSCREEN;

}

GraphicalPlatformConfig::GraphicalPlatformConfig(const string &name) 
    : PlatformConfig(name) {
    
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

GraphicalPlatformConfig *GraphicalPlatformConfig::Load(xml_node &xmlNode) {   
    
    GraphicalPlatformConfig *newConfig = new GraphicalPlatformConfig(string(xmlNode.attribute("typeName")));

    xml_node widthNode = xmlNode.child("Width");
    if (widthNode)
        newConfig->width = widthNode.text().as_int();

    xml_node *heightNode = xmlNode.child("Height");
    if (heightNode)
        newConfig->height = heightNode.text().as_int();

    xml_node fullscreenNode = xmlNode.child("Fullscreen");
    if (fullscreenNode)
        newConfig->height = fullscreenNode.text().as_bool();

    return newConfig;

}

int GraphicalPlatformConfig::GetWidth() { return this->width; }
void GraphicalPlatformConfig::SetWidth(int width) { this->width = width; }

int GraphicalPlatformConfig::GetHeight() { return this->height; }
void GraphicalPlatformConfig::SetHeight(int width) { this->height = height; }

bool GraphicalPlatformConfig::GetFullscreen() { return this->fullscreen; }
void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }
