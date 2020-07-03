/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define DEFAULT_LOG_FILENAME "engine.log"
#define DEFAULT_ENGINECONFIG_FILENAME "default.engine_config"

#define EXTENSION_ENGINECONFIG "engine_config"

#define XMLNAME_ENGINECONFIG "EngineConfig"
#define XMLNAME_ENGINECONFIG_LOGFILENAME "LogFilename"
#define XMLNAME_ENGINECONFIG_PLATFORMCONFIG XMLNAME_PLATFORMCONFIG
#define XMLNAME_ENGINECONFIG_ADDIN XMLNAME_ADDININFO

/**
 * EngineConfig provides the setup details for the engine.
 */
class EngineConfig : public XmlData {

private:

    unique_ptr<string> log_filename_;

    vector<string> addin_filenames_;

    unique_ptr<PlatformConfig> platform_config_;

protected:

    EngineConfig(const string &filename);

public:

    const string &GetLogFilename() const;
    void SetLogFilename(const string &log_filename);

    void AddAddinFilename(const string &addin_filename);
    const vector<reference_wrapper<const string>> GetAddinFilenames();

    PlatformConfig* GetPlatformConfig() const;
    void SetPlatformConfig(PlatformConfig* config);

    using XmlData::Load;
    using XmlData::Save;

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

private:

    class Loader : public DataLoader {
    private:

        static Loader singleton;

        Loader();

    public:

        Data *Load(const string &filename);

    };

};
