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
#define XMLNAME_ENGINECONFIG_ADDIN XMLNAME_ADDINHEADER

    /**
     * EngineConfig provides the setup details for the engine_.
     */
    class GAME_API EngineConfig : public content::XmlContent {

    private:

        std::unique_ptr<std::string> log_filename_;

        std::vector<std::string> addin_filenames_;

        std::unique_ptr<platform::PlatformConfig> platform_config_;

    protected:

        EngineConfig(const std::string& filename);

    public:

        const std::string& GetLogFilename() const;
        void SetLogFilename(const std::string& log_filename);

        void AddAddinFilename(const std::string& addin_filename);
        const std::vector<std::reference_wrapper<const std::string>> GetAddinFilenames();

        platform::PlatformConfig* GetPlatformConfig() const;
        void SetPlatformConfig(platform::PlatformConfig* config);

        using content::XmlContent::Load;
        using content::XmlContent::Save;

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

    private:

        class Loader : public ILoader {
        private:

            static Loader singleton;

            Loader();

        public:

            content::Content* Load(const std::string& filename);

        };

    };

}
