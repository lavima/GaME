#include "../GaME.h"

using namespace game::graphics::vulkan;

#include "Config.h"
#include "SimpleRenderer.h"

namespace game::simplerenderer {

    Config::Config(data::xml::XmlNode root_node) : SystemConfig(root_node) {}

    bool Config::Load(data::xml::XmlNode root_node) {
        if (!SystemConfig::Load(root_node))
            return false;

        return true;
    }

    bool Config::Save(data::xml::XmlNode root_node) {
        if (!SystemConfig::Save(root_node))
            return false;

        return true;
    }

    Config::Loader* Config::Loader::singleton_ = nullptr;

    Config::Loader::Loader() {
        SystemConfig::RegisterType(SIMPLERENDERER_TYPENAME, this);
    }

    Config::Loader* Config::Loader::Get() {
        if (!singleton_)
            singleton_ = new Loader();
        return singleton_;
    }

    SystemConfig* Config::Loader::Load(data::xml::XmlNode root_node) {
        return new Config(root_node);
    }

}