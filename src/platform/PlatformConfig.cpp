/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

PlatformConfig::PlatformConfig(const string &typeName) {

    this->typeName = typeName;

}

const string &PlatformConfig::GetTypeName() { return typeName; }
void PlatformConfig::SetTypeName(const string &typeName) { this->typeName = typeName; }

PlatformConfig *PlatformConfig::Load(xml_document &xmlDocument) {

    xml_node xmlNode = xmlDocument.document_element();
    if (string(xmlNode.value()).compare("GraphicalPlatformConfig") == 0)
        return new GraphicalPlatformConfig(xmlNode);

    return new PlatformConfig("Undecided");

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

GraphicalPlatformConfig::GraphicalPlatformConfig(xml_node &xmlNode) : PlatformConfig(string(xmlNode.attribute("typeName").value())) {   
    
    xml_node widthNode = xmlNode.child("Width");
    if (widthNode)
        this->width = widthNode.text().as_int();

    xml_node heightNode = xmlNode.child("Height");
    if (heightNode)
        this->height = heightNode.text().as_int();

    xml_node fullscreenNode = xmlNode.child("Fullscreen");
    if (fullscreenNode)
        this->height = fullscreenNode.text().as_bool();

}

int GraphicalPlatformConfig::GetWidth() { return this->width; }
void GraphicalPlatformConfig::SetWidth(int width) { this->width = width; }

int GraphicalPlatformConfig::GetHeight() { return this->height; }
void GraphicalPlatformConfig::SetHeight(int width) { this->height = height; }

bool GraphicalPlatformConfig::GetFullscreen() { return this->fullscreen; }
void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }
