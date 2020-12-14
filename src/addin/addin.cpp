/*
File: Addin.cpp
Author: Lars Vidar Magnusson
 */

#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <sstream>
#include <optional>
#include <list>
#include <unordered_map>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <pugixml.hpp>
#include <v8.h>

#include "../global.h"
#include "../lib/string_util.h"
#include "../lib/file_path.h"
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
#include "../framework/system_config.h"
#include "../framework/game_time.h"
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
#include "system_provider.h"
#include "addin_header.h"
#include "addin.h"
#include "../log.h"
#include "../engine_config.h"
#include "../engine.h"

namespace game::addin {

    Addin::Addin(AddinHeader* header) 
        : handle_(nullptr), header_(std::unique_ptr<AddinHeader>(header)), register_fun_(nullptr) {}

    Addin::~Addin() {}
    
    void Addin::Register(Engine& engine, AddinHeader& header) {
     
        assert(register_fun_);

        AddinBindingInfo binding_info;
        register_fun_(engine, header, &binding_info);

        if (binding_info.type_flags&AddinType::System) {
            for (auto& system_info:header.GetSystemInfos()) {
                const std::string& type_name = system_info.get().GetName();
                framework::SystemConfig::RegisterType(type_name, binding_info.system_provider);
                framework::System::RegisterType(type_name, binding_info.system_provider);
            }
        }

        if (binding_info.type_flags&AddinType::Component) {
            for (auto& component_info:header.GetComponentInfos()) {
                const std::string& type_name = component_info.get().GetName();
                framework::Component::RegisterType(type_name, binding_info.component_provider);
                framework::ComponentConfig::RegisterType(type_name, binding_info.component_provider);
            }
        }

    }

    Addin* Addin::Load(Engine& engine, const std::string& filename) {

        Addin* addin = new Addin(content::Content::Load<AddinHeader>(filename));
        AddinHeader& header = addin->GetHeader();

        std::string libraryFilename = lib::FilePath::GetFilename(header.GetLibraryFilename());

        addin->handle_ = engine.GetPlatform().LoadLibrary(libraryFilename);
        if (!addin->handle_) {
            delete addin;
            return nullptr;
        }

        AddinFun_Register register_fun = engine.GetPlatform().LoadLibrarySymbol<ADDINFUN_REGISTER_TEMPLATE>(addin->handle_, ADDINFUN_REGISTERADDIN);
        if (!register_fun) {
            delete addin;
            return nullptr;
        }
        addin->register_fun_ = register_fun;

        addin->Register(engine, header);

        return addin;

    }

    bool Addin::Unload(Engine& engine) {

        if (!handle_)
            return false;

        engine.GetPlatform().UnloadLibrary(handle_);

        return true;

    }


    AddinHeader& Addin::GetHeader() { return *(this->header_); }

    AddinType Addin::GetType() const {
        return header_->GetType();
    }
    
}
