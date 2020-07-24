/*
File: ScriptContext.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::scripting {

    class game::Engine;
    class Script;

    class GAME_API ScriptEnvironment {

        friend class V8;

    protected:

        Engine* engine;

        v8::Isolate* isolate;
        v8::ArrayBuffer::Allocator* allocator;

        v8::Persistent<v8::Context> context;

        ScriptEnvironment(Engine& engine);

    public:

        ~ScriptEnvironment();

        static ScriptEnvironment* Create(Engine&);

        Script* LoadScript(const std::string&);
        v8::Handle<v8::Value> RunScript(Script&);

        v8::Isolate* GetIsolate();
        v8::ArrayBuffer::Allocator* GetAllocator();
        v8::Local<v8::Context> GetContext();

    };

}