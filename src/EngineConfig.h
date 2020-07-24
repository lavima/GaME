/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

#define DEFAULT_LOG_FILENAME "engine.log"
#define DEFAULT_ENGINECONFIG_FILENAME "default.engine_config"

#define EXTENSION_ENGINECONFIG "engine_config"

#define XMLNAME_ENGINECONFIG "EngineConfig"
#define XMLNAME_ENGINECONFIG_LOGFILENAME "LogFilename"
#define XMLNAME_ENGINECONFIG_PLATFORMCONFIG XMLNAME_PLATFORMCONFIG
#define XMLNAME_ENGINECONFIG_ADDIN XMLNAME_ADDININFO

    /**
     * EngineConfig provides the setup details for the engine_.
     */
    class GAME_API EngineConfig : public data::XmlData {

    private:

        unique_ptr<string> log_filename_;

        vector<string> addin_filenames_;

        unique_ptr<platform::PlatformConfig> platform_config_;

    protected:

        EngineConfig(const string& filename);

    public:

        const string& GetLogFilename() const;
        void SetLogFilename(const string& log_filename);

        void AddAddinFilename(const string& addin_filename);
        const vector<reference_wrapper<const string>> GetAddinFilenames();

        platform::PlatformConfig* GetPlatformConfig() const;
        void SetPlatformConfig(platform::PlatformConfig* config);

        using XmlData::Load;
        using XmlData::Save;

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

    private:

        class Loader : public DataLoader {
        private:

            static Loader singleton;

            Loader();

        public:

            Data* Load(const string& filename);

        };

    };

}