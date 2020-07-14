/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

unordered_map<string, PlatformConfig::Loader*>* PlatformConfig::configuration_loaders_ = nullptr;

PlatformConfig::PlatformConfig(const string& implementation_name) {

    this->implementation_name_ = implementation_name;

}

void PlatformConfig::RegisterImplementation(const string& implementation_name, PlatformConfig::Loader* loader) {

    if (!configuration_loaders_)
        configuration_loaders_ = new unordered_map<string, PlatformConfig::Loader*>();

    configuration_loaders_->insert_or_assign(implementation_name, loader);

}

PlatformConfig* PlatformConfig::Create(XmlNode root_node) {
   
    if (!configuration_loaders_)
        return nullptr;

    const string implementation_name = root_node.GetAttribute("implementation").GetValue();
   
    return configuration_loaders_->at(implementation_name)->Load(implementation_name, root_node);
}

const string &PlatformConfig::GetImplementationName() { return implementation_name_; }
void PlatformConfig::SetImplementationName(const string &typeName) { this->implementation_name_ = typeName; }


GraphicalPlatformConfig::GraphicalPlatformConfig(const string& implementation_name)
    : PlatformConfig(implementation_name) {

    this->width_ = DEFAULT_GRAPHICALPLATFORM_WIDTH;
    this->height_ = DEFAULT_GRAPHICALPLATFORM_HEIGHT;
    this->fullscreen_ = DEFAULT_GRAPHICALPLATFORM_FULLSCREEN;

}

GraphicalPlatformConfig::GraphicalPlatformConfig(const string& implementation_name, int width, int height, bool fullscreen) 
    : PlatformConfig(implementation_name) {

    this->width_ = width;
    this->height_ = height;
    this->fullscreen_ = fullscreen;

}

bool GraphicalPlatformConfig::Load(XmlNode root_node) {

    if (root_node.GetName().compare(XMLNAME_PLATFORMCONFIG))
        return false;

    XmlNode width_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_WIDTH);
    if (!width_node)
        return false;
    const string& value = width_node.GetValue();
    width_ = stoi(width_node.GetValue());

    XmlNode height_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_HEIGHT);
    if (!height_node)
        return false;
    height_ = stoi(height_node.GetValue());

    XmlNode fullscreen_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_FULLSCREEN);
    if (!fullscreen_node)
        fullscreen_ = false;
    fullscreen_ = true;

    return true;

}

bool GraphicalPlatformConfig::Save(XmlNode root_node) {

    root_node.SetName(XMLNAME_PLATFORMCONFIG);

    XmlNode width_node = root_node.AddChild(XMLNAME_PLATFORMCONFIG_WIDTH);
    width_node.SetValue(to_string(width_));

    XmlNode height_node = root_node.AddChild(XMLNAME_PLATFORMCONFIG_HEIGHT);
    height_node.SetValue(to_string(height_));

    if (fullscreen_)
        root_node.AddChild(XMLNAME_PLATFORMCONFIG_FULLSCREEN);

    return true;

}

uint32_t GraphicalPlatformConfig::GetWidth() const { return this->width_; }
void GraphicalPlatformConfig::SetWidth(uint32_t width) { this->width_ = width; }

uint32_t GraphicalPlatformConfig::GetHeight() const { return this->height_; }
void GraphicalPlatformConfig::SetHeight(uint32_t width) { this->height_ = height_; }

bool GraphicalPlatformConfig::GetFullscreen() const { return this->fullscreen_; }
void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { this->fullscreen_ = fullscreen; }
