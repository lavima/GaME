/*
File: ScriptContext.h
Author: Lars Vidar Magnusson
 */

#pragma once

class Engine;
class Script;

class ScriptEnvironment {

    friend class V8;
    friend class Scriptable;

private:

    Engine *engine;

    v8::Isolate *isolate;
    v8::ArrayBuffer::Allocator *allocator;

    v8::Persistent<v8::Context> context;

    ScriptEnvironment(Engine &engine);

public:

    ~ScriptEnvironment();

    static ScriptEnvironment *Create(Engine &);

    Script *LoadScript(const std::string &);
    v8::Handle<v8::Value> RunScript(Script &);

    v8::Persistent<v8::Context> GetContext();

};
