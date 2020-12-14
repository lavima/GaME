#include "../game.h"

using namespace game::graphics::vulkan;

#include "config.h"
#include "mesh_component.h"
#include "renderer.h"

namespace game::vulkanrenderer {

    Config::Config() {}

    bool Config::Load(content::xml::XmlNode root_node) {
        if (!SystemConfig::Load(root_node))
            return false;

        return true;
    }

    bool Config::Save(content::xml::XmlNode root_node) {
        if (!SystemConfig::Save(root_node))
            return false;

        return true;
    }

    uint32_t Config::GetFramesInFlight() { 
        return frames_in_flight_;
    }
}
