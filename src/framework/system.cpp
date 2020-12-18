/*
File: system.cpp
Author: Lars Vidar Magnusson
 */

#include <functional>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <algorithm>
#include <optional>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <pugixml.hpp>
#include <v8.h>

#include "../global.h"
#include "../lib/format.h"
#include "../lib/file_path.h"
#include "../log.h"
#include "../content/content.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "../scripting/script_environment.h"
#include "../scripting/script.h"
#include "../scripting/scriptable.h"
#include "../platform/input_key.h"
#include "../platform/platform_config.h"
#include "../platform/platform.h"
#include "framework.h"
#include "component_info.h"
#include "component_config.h"
#include "system_info.h"
#include "system_config.h"
#include "game_time.h"
#include "component.h"
#include "entity_specification.h"
#include "entity.h"
#include "game_config.h"
#include "game_header.h"
#include "game_specification.h"
#include "game.h"
#include "system.h"
#include "../addin/system_provider.h"
#include "../addin/addin_header.h"
#include "../addin/addin.h"
#include "../engine_config.h"
#include "../engine.h"

namespace game::framework {

#ifndef DLL_BUILD
    std::unordered_map<std::string, System::ICreator*>* System::creators_ = nullptr;
#endif

    System::System(Engine& engine, const SystemInfo& info, SystemConfig& config) : info_(info) {

        engine_ = &engine;

        config_ = &config;

    }

    System::~System() {}

    Engine& System::GetEngine() {
        return *engine_;
    }

    const SystemInfo& System::GetInfo() const {
        return info_;
    }

    SystemConfig& System::GetConfig() {
        return *config_;
    }

    System* System::Create(Engine& engine, SystemConfig& config) {

        assert(creators_);

        if (!IsTypeAvailable(config.GetTypeName())) {
            LOG_ERROR("Could not find the specified system type %0", config.GetTypeName());
            return nullptr;
        }

        return (*creators_)[config.GetTypeName()]->Create(engine, config);

    }

    void System::RegisterType(const std::string& typeName, ICreator* creator) {

        if (!creators_)
            creators_ = new std::unordered_map<std::string, ICreator*>();

        creators_->insert_or_assign(typeName, creator);

    }

    bool System::IsTypeAvailable(const std::string& type_name) {
        
        auto iter = creators_->find(type_name);
        if (iter==creators_->end())
            return false;

        return true;

    }

}
