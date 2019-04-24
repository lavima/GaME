/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

PlatformConfig::PlatformConfig(const string &filename) : XMLData(filename) {}
PlatformConfig::PlatformConfig(const string &filename, xml_document *document) : XMLData(filename, document) {}

PlatformConfig::PlatformConfig(const string &filename, const string &typeName)
    : XMLData(filename) {

    this->typeName = typeName;

}

const string &PlatformConfig::GetTypeName() { return typeName; }
void PlatformConfig::SetTypeName(const string &typeName) { this->typeName = typeName; }


PlatformConfig::__Factory PlatformConfig::__Factory::singleton;
PlatformConfig::__Factory::__Factory() { Data::RegisterType(PLATFORM_CONFIG_EXTENSION, &singleton); }

Data *PlatformConfig::__Factory::Load(const string &filename) {

    xml_document *document = new xml_document(); 
   
    if (XMLData::Parse(filename, document))
        return nullptr;

    PlatformConfig *platformConfig = nullptr;

    xml_node xmlNode = document->document_element();
    if (string(xmlNode.value()).compare("GraphicalPlatformConfig") == 0)
        platformConfig = new GraphicalPlatformConfig(filename, document);
    else
        return nullptr;

    if (!platformConfig->Load(xmlNode))
        return nullptr;

    return platformConfig;

}


GraphicalPlatformConfig::GraphicalPlatformConfig(const string &filename) : PlatformConfig(filename) {} 
GraphicalPlatformConfig::GraphicalPlatformConfig(const string &filename, xml_document *document) : PlatformConfig(filename, document) {}

GraphicalPlatformConfig::GraphicalPlatformConfig(const string &filename, const string &typeName) 
    : PlatformConfig(filename, typeName) {
    
    this->width = DEFAULT_GRAPHICALPLATFORM_WIDTH;
    this->height = DEFAULT_GRAPHICALPLATFORM_HEIGHT;
    this->fullscreen = DEFAULT_GRAPHICALPLATFORM_FULLSCREEN;

}

GraphicalPlatformConfig::GraphicalPlatformConfig(const string &filename, const string &typeName, int width, int height, bool fullscreen) 
    : PlatformConfig(filename, typeName) {

    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;

}

bool GraphicalPlatformConfig::Load(xml_node rootNode) {

    if (string(rootNode.name()).compare(XMLNAME_GRAPHICALPLATFORMCONFIG))
        return false;

    xml_node widthNode = rootNode.child(XMLNAME_GRAPHICALPLATFORMCONFIG_WIDTH);
    if (!widthNode)
        return false;
    width = widthNode.text().as_int();

    xml_node heightNode = rootNode.child(XMLNAME_GRAPHICALPLATFORMCONFIG_HEIGHT);
    if (!heightNode)
        return false;
    height = heightNode.text().as_int();

    xml_node fullscreenNode = rootNode.child(XMLNAME_GRAPHICALPLATFORMCONFIG_FULLSCREEN);
    if (!fullscreenNode)
        fullscreen = false;
    fullscreen = true;

    return true;

}

bool GraphicalPlatformConfig::Save(xml_node rootNode) {

    rootNode.set_name(XMLNAME_GRAPHICALPLATFORMCONFIG);

    xml_node widthNode = rootNode.append_child(XMLNAME_GRAPHICALPLATFORMCONFIG_WIDTH);
    widthNode.set_value(to_string(width).c_str());

    xml_node heightNode = rootNode.append_child(XMLNAME_GRAPHICALPLATFORMCONFIG_HEIGHT);
    heightNode.set_value(to_string(height).c_str());

    if (fullscreen)
        rootNode.append_child(XMLNAME_GRAPHICALPLATFORMCONFIG_FULLSCREEN);

    return true;

}

int GraphicalPlatformConfig::GetWidth() { return this->width; }
void GraphicalPlatformConfig::SetWidth(int width) { this->width = width; }

int GraphicalPlatformConfig::GetHeight() { return this->height; }
void GraphicalPlatformConfig::SetHeight(int width) { this->height = height; }

bool GraphicalPlatformConfig::GetFullscreen() { return this->fullscreen; }
void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }
