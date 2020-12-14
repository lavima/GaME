/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <pugixml.hpp>

#include "../global.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "platform_config.h"

namespace game::platform {

    std::unordered_map<std::string, PlatformConfig::Loader*>* PlatformConfig::configuration_loaders_ = nullptr;

    PlatformConfig::PlatformConfig(const std::string& implementation_name) {

        this->implementation_name_ = implementation_name;

    }

    PlatformConfig::~PlatformConfig() {}

    void PlatformConfig::RegisterImplementation(const std::string& implementation_name, PlatformConfig::Loader* loader) {

        if (!configuration_loaders_)
            configuration_loaders_ = new std::unordered_map<std::string, PlatformConfig::Loader*>();

        configuration_loaders_->insert_or_assign(implementation_name, loader);

    }

    PlatformConfig* PlatformConfig::Create(content::xml::XmlNode root_node) {

        if (!configuration_loaders_)
            return nullptr;

        const std::string implementation_name = root_node.GetAttribute("implementation").GetValue();

        return configuration_loaders_->at(implementation_name)->Load(implementation_name, root_node);
    }

    const std::string& PlatformConfig::GetImplementationName() { return implementation_name_; }
    void PlatformConfig::SetImplementationName(const std::string& typeName) { this->implementation_name_ = typeName; }


    GraphicalPlatformConfig::GraphicalPlatformConfig(const std::string& implementation_name)
        : PlatformConfig(implementation_name) {

        this->width_ = DEFAULT_GRAPHICALPLATFORM_WIDTH;
        this->height_ = DEFAULT_GRAPHICALPLATFORM_HEIGHT;
        this->fullscreen_ = DEFAULT_GRAPHICALPLATFORM_FULLSCREEN;

    }

    GraphicalPlatformConfig::GraphicalPlatformConfig(const std::string& implementation_name, int width, int height, bool fullscreen)
        : PlatformConfig(implementation_name) {

        this->width_ = width;
        this->height_ = height;
        this->fullscreen_ = fullscreen;

    }

    bool GraphicalPlatformConfig::Load(content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_PLATFORMCONFIG))
            return false;

        content::xml::XmlNode width_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_WIDTH);
        if (!width_node)
            return false;
        width_ = stoi(width_node.GetValue());

        content::xml::XmlNode height_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_HEIGHT);
        if (!height_node)
            return false;
        height_ = stoi(height_node.GetValue());

        content::xml::XmlNode fullscreen_node = root_node.GetChild(XMLNAME_PLATFORMCONFIG_FULLSCREEN);
        if (!fullscreen_node)
            fullscreen_ = false;
        fullscreen_ = true;

        return true;

    }

    bool GraphicalPlatformConfig::Save(content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_PLATFORMCONFIG);

        content::xml::XmlNode width_node = root_node.AddChild(XMLNAME_PLATFORMCONFIG_WIDTH);
        width_node.SetValue(std::to_string(width_));

        content::xml::XmlNode height_node = root_node.AddChild(XMLNAME_PLATFORMCONFIG_HEIGHT);
        height_node.SetValue(std::to_string(height_));

        if (fullscreen_)
            root_node.AddChild(XMLNAME_PLATFORMCONFIG_FULLSCREEN);

        return true;

    }

    uint32_t GraphicalPlatformConfig::GetWidth() const { return width_; }
    void GraphicalPlatformConfig::SetWidth(uint32_t width) { width_ = width; }

    uint32_t GraphicalPlatformConfig::GetHeight() const { return height_; }
    void GraphicalPlatformConfig::SetHeight(uint32_t height) { height_ = height; }

    bool GraphicalPlatformConfig::GetFullscreen() const { return fullscreen_; }
    void GraphicalPlatformConfig::SetFullscreen(bool fullscreen) { fullscreen_ = fullscreen; }

}
