/*
* File: ScriptEnvironment.cpp
* Author: Lars Vidar Magnusson
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
#include <libplatform/libplatform.h>

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
#include "../addin/system_provider.h"
#include "../addin/addin_header.h"
#include "../addin/addin.h"
#include "../log.h"
#include "../engine_config.h"
#include "../engine.h"

namespace game::scripting {

    ScriptEnvironment::ScriptEnvironment(Engine& engine) {

        this->engine = &engine;

    }

    ScriptEnvironment::~ScriptEnvironment() {

        isolate->Dispose();
        delete allocator;

    }

    ScriptEnvironment* ScriptEnvironment::Create(Engine& engine) {

        ScriptEnvironment* env = new ScriptEnvironment(engine);

        v8::V8::InitializeICUDefaultLocation(engine.GetInfo().GetExecutablePath().c_str());
        v8::V8::InitializeExternalStartupData(engine.GetInfo().GetExecutablePath().c_str());
        std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(platform.get());
        v8::V8::Initialize();

        v8::Isolate::CreateParams createParams;
        env->allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        createParams.array_buffer_allocator = env->allocator;

        env->isolate = v8::Isolate::New(createParams);
        {
            v8::Isolate::Scope isolateScope(env->isolate);
            v8::HandleScope handleScope(env->isolate);

            //v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(env->isolate);
            //env->context = v8::Persistent<v8::Context>(env->isolate, v8::Context::New(env->isolate, NULL, global));
        }

        return env;

    }

    Script* ScriptEnvironment::LoadScript(const std::string& filename) {
        return nullptr;
    }

    v8::Local<v8::Value> ScriptEnvironment::RunScript(Script& script) {
        return v8::Local<v8::Value>();
    }

    v8::Isolate* ScriptEnvironment::GetIsolate() { return isolate; }
    v8::ArrayBuffer::Allocator* ScriptEnvironment::GetAllocator() { return allocator; }
    v8::Local<v8::Context> ScriptEnvironment::GetContext() { return context.Get(isolate); }

}
