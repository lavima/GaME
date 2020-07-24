#pragma once

namespace game::simplerenderer {

    const int DEFAULT_FRAMES_IN_FLIGHT = 2;

#define XMLNAME_CONFIG_FRAMES_IN_FLIGHT "FramesInFlight"

    class Config : public SystemConfig {
    private:

        uint32_t frames_in_flight_;

    public:
        
        Config(XmlNode root_node);

        bool Load(XmlNode root_node) override;
        bool Save(XmlNode root_node) override;

        class Loader : public SystemConfig::Loader {
        private:
            static Loader* singleton_;
            Loader();
        public:
            static Loader* Get();
            SystemConfig* Load(XmlNode root_node) override;
        };

    };

}