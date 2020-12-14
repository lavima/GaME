/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <pugixml.hpp>

#include "global.h"
#include "lib/file_path.h"
#include "content/xml/xml_range.h"
#include "content/xml/xml_attribute.h"
#include "content/xml/xml_node.h"
#include "content/xml/xml_document.h"
#include "content/xml/xml_serializable.h"
#include "content/content.h"
#include "content/xml_content.h"
#include "platform/platform_config.h"
#include "version.h"
#include "version_info.h"
#include "framework/system_info.h"
#include "framework/component_Info.h"
#include "addin/addin_header.h"
#include "engine_config.h"

namespace game {

    EngineConfig::EngineConfig(const std::string& filename) : content::XmlContent(filename) {}
    EngineConfig::~EngineConfig() {}


    const std::string& EngineConfig::GetLogFilename() const {
        static std::string empty = "";
        return log_filename_ ? *log_filename_ : empty;
    }

    void EngineConfig::SetLogFilename(const std::string& logFilename) {
        log_filename_ = std::unique_ptr<std::string>(new std::string(logFilename));
    }

    void EngineConfig::AddAddinFilename(const std::string& addinFilename) { 
        addin_filenames_.push_back(addinFilename); 
    }

    const std::vector<std::reference_wrapper<const std::string>> EngineConfig::GetAddinFilenames() {
        return std::vector<std::reference_wrapper<const std::string>>(addin_filenames_.begin(), addin_filenames_.end());
    }

    platform::PlatformConfig* EngineConfig::GetPlatformConfig() const {
        return platform_config_.get();
    }

    void EngineConfig::SetPlatformConfig(platform::PlatformConfig* config) {
        platform_config_ = std::unique_ptr<platform::PlatformConfig>(config);
    }

    bool EngineConfig::Load(content::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_ENGINECONFIG))
            return false;

        content::xml::XmlNode log_filename_node = root_node.GetChild(XMLNAME_ENGINECONFIG_LOGFILENAME);
        if (!log_filename_node)
            log_filename_ = std::unique_ptr<std::string>(new std::string(DEFAULT_LOG_FILENAME));
        else
            log_filename_ = std::unique_ptr<std::string>(new std::string(log_filename_node.GetValue()));

        content::xml::XmlNode platform_config_node = root_node.GetChild(XMLNAME_ENGINECONFIG_PLATFORMCONFIG);
        if (platform_config_node)
            platform_config_ = std::unique_ptr<platform::PlatformConfig>(platform::PlatformConfig::Create(platform_config_node));

        if (!platform_config_)
            return false;

        for (content::xml::XmlNode addin_node : root_node.GetChildren(XMLNAME_ENGINECONFIG_ADDIN)) {
            addin_filenames_.push_back(addin_node.GetValue());
        }

        return true;

    }

    bool EngineConfig::Save(content::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_ENGINECONFIG);

        content::xml::XmlNode log_filename_node = root_node.AddChild(XMLNAME_ENGINECONFIG_LOGFILENAME);
        log_filename_node.SetValue(*log_filename_);

        for (const std::string& addinFilename:addin_filenames_) {
            content::xml::XmlNode addin_filename_node = root_node.AddChild(XMLNAME_ENGINECONFIG_ADDIN);
            addin_filename_node.SetValue(addinFilename.c_str());
        }

        return true;

    }


    EngineConfig::Loader EngineConfig::Loader::singleton;

    EngineConfig::Loader::Loader() { content::Content::RegisterType(EXTENSION_ENGINECONFIG, &singleton); }

    content::Content* EngineConfig::Loader::Load(const std::string& filename) {

        EngineConfig* newConfig = new EngineConfig(filename);

        if (!newConfig->Load())
            return nullptr;

        return newConfig;

    }

}
