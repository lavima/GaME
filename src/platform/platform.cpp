/*
File: Platform.cpp
Author: Lars Vidar Magnusson
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <pugixml.hpp>
#include <v8.h>

#include "../global.h"
#include "../lib/file_path.h"
#include "../lib/string_util.h"
#include "../content/xml/xml_range.h"
#include "../content/xml/xml_attribute.h"
#include "../content/xml/xml_node.h"
#include "../content/xml/xml_document.h"
#include "../content/xml/xml_serializable.h"
#include "../content/content.h"
#include "../content/xml_content.h"
#include "../version.h"
#include "../version_info.h"
#include "../scripting/script_environment.h"
#include "../scripting/script.h"
#include "../scripting/scriptable.h"
#include "../platform/input_key.h"
#include "../platform/platform_config.h"
#include "../platform/platform.h"
#include "../framework/framework.h"
#include "../framework/system_info.h"
#include "../framework/game_time.h"
#include "../framework/system_config.h"
#include "../framework/component_config.h"
#include "../framework/component.h"
#include "../framework/entity_specification.h"
#include "../framework/entity.h"
#include "../framework/game_header.h"
#include "../framework/game_config.h"
#include "../framework/game_specification.h"
#include "../framework/game.h"
#include "../framework/system.h"
#include "../framework/component_info.h"
#include "../addin/system_provider.h"
#include "../addin/addin_header.h"
#include "../addin/addin.h"
#include "../log.h"
#include "../engine_config.h"
#include "../engine.h"
#include "platform_config.h"
#include "platform.h"

namespace game::platform {

    // 
    // Declare the static member pointer. The creation of the object uses a First Use idiom 
    // to avoid static fiasco.
    //
    std::unordered_map<std::string, Platform::Creator*>* Platform::implementations_ = nullptr;

    Platform::Platform(const std::string& name, Engine& engine, PlatformConfig& config)
        : implementation_name_(name), engine_(engine), config_(config) {}

    Platform::~Platform() {}

    Platform* Platform::Create(Engine& engine, PlatformConfig& config) {

        if (!implementations_->count(config.GetImplementationName()))
            return nullptr;

        Platform::Creator* creator =
            (Platform::Creator*)implementations_->at(config.GetImplementationName());

        return creator->Create(engine, config);
    }

    const std::unordered_map<KeyCode, std::reference_wrapper<const InputKey>> Platform::GetInputKeys() {
        return std::unordered_map<KeyCode, std::reference_wrapper<const InputKey>>(input_keys_.begin(), input_keys_.end());
    }

    void Platform::RegisterImplementation(const std::string& name, Platform::Creator* creator) {

        if (!implementations_)
            implementations_ = new std::unordered_map<std::string, Platform::Creator*>();

        implementations_->insert_or_assign(name, creator);

    }

    LibraryHandle Platform::LoadLibrary(const std::string& filename) {
#ifdef _WINDOWS
        HMODULE handle = LoadLibraryA(filename.c_str());
#endif
        return handle;
    }

    void Platform::UnloadLibrary(LibraryHandle handle) {

    }

    Engine& Platform::GetEngine() { return engine_; }
    PlatformConfig& Platform::GetConfig() { return config_; }
    std::unordered_map<KeyCode, InputKeyWritable> Platform::GetWritableInputKeys() { return input_keys_; }

}
