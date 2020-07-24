/*
File: EngineConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

namespace game {

    EngineConfig::EngineConfig(const string& filename) : XmlData(filename) {}


    const string& EngineConfig::GetLogFilename() const {
        return log_filename_ ? *log_filename_ : "";
    }

    void EngineConfig::SetLogFilename(const string& logFilename) {
        log_filename_ = unique_ptr<string>(new string(logFilename));
    }

    void EngineConfig::AddAddinFilename(const string& addinFilename) { addin_filenames_.push_back(addinFilename); }

    const vector<reference_wrapper<const string>> EngineConfig::GetAddinFilenames() {
        return vector<reference_wrapper<const string>>(addin_filenames_.begin(), addin_filenames_.end());
    }

    platform::PlatformConfig* EngineConfig::GetPlatformConfig() const {
        return platform_config_.get();
    }

    void EngineConfig::SetPlatformConfig(platform::PlatformConfig* config) {
        platform_config_ = unique_ptr<platform::PlatformConfig>(config);
    }

    bool EngineConfig::Load(data::xml::XmlNode root_node) {

        if (root_node.GetName().compare(XMLNAME_ENGINECONFIG))
            return false;

        data::xml::XmlNode log_filename_node = root_node.GetChild(XMLNAME_ENGINECONFIG_LOGFILENAME);
        if (!log_filename_node)
            log_filename_ = unique_ptr<string>(new string(DEFAULT_LOG_FILENAME));
        else
            log_filename_ = unique_ptr<string>(new string(log_filename_node.GetValue()));

        data::xml::XmlNode platform_config_node = root_node.GetChild(XMLNAME_ENGINECONFIG_PLATFORMCONFIG);
        if (platform_config_node)
            platform_config_ = unique_ptr<platform::PlatformConfig>(platform::PlatformConfig::Create(platform_config_node));

        if (!platform_config_)
            return false;

        for (data::xml::XmlNode addin_node : root_node.GetChildren(XMLNAME_ENGINECONFIG_ADDIN)) {
            const string& value = addin_node.GetValue();
            addin_filenames_.push_back(addin_node.GetValue());
        }

        return true;

    }

    bool EngineConfig::Save(data::xml::XmlNode root_node) {

        root_node.SetName(XMLNAME_ENGINECONFIG);

        data::xml::XmlNode log_filename_node = root_node.AddChild(XMLNAME_ENGINECONFIG_LOGFILENAME);
        log_filename_node.SetValue(*log_filename_);

        for (const string& addinFilename:addin_filenames_) {
            data::xml::XmlNode addin_filename_node = root_node.AddChild(XMLNAME_ENGINECONFIG_ADDIN);
            addin_filename_node.SetValue(addinFilename.c_str());
        }

        return true;

    }


    EngineConfig::Loader EngineConfig::Loader::singleton;

    EngineConfig::Loader::Loader() { Data::RegisterType(EXTENSION_ENGINECONFIG, &singleton); }

    data::Data* EngineConfig::Loader::Load(const string& filename) {

        EngineConfig* newConfig = new EngineConfig(filename);

        if (!newConfig->Load())
            return nullptr;

        return newConfig;

    }

}