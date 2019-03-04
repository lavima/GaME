/*
* File: ScriptEnvironment.cpp
* Author: Lars Vidar Magnusson
*/

#include "../GaME.h"


ScriptEnvironment::ScriptEnvironment(Engine &engine) {

    this->engine = &engine;

}

ScriptEnvironment::~ScriptEnvironment() {

    isolate->Dispose();
    delete allocator;

}

ScriptEnvironment *ScriptEnvironment::Create(Engine &engine) {

    ScriptEnvironment *env = new ScriptEnvironment(engine);

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

        v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(env->isolate);
        //env->context = v8::Persistent<v8::Context>(env->isolate, v8::Context::New(env->isolate, NULL, global));
    }

    return env;

}

Script * ScriptEnvironment::LoadScript(const string &filename) {
    return nullptr;
}

v8::Handle<v8::Value> ScriptEnvironment::RunScript(Script &script) {
    return v8::Handle<v8::Value>();
}

v8::Isolate *ScriptEnvironment::GetIsolate() { return isolate; }
v8::ArrayBuffer::Allocator *ScriptEnvironment::GetAllocator() { return allocator; }
v8::Local<v8::Context> ScriptEnvironment::GetContext() { return context.Get(isolate); }

