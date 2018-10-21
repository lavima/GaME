/*
File: ScriptContext.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"


ScriptEnvironment::ScriptEnvironment(Engine &engine) {

    this->engine = &engine;

}

ScriptEnvironment::~ScriptEnvironment() {
  
  isolate->Dispose();
  delete allocator;

}

ScriptEnvironment *ScriptEnvironment::Load(Engine &engine) {

  ScriptEnvironment *env = new ScriptEnvironment(engine);

  v8::V8::InitializeICUDefaultLocation(engine.GetInfo().ExecutablePath.c_str());
  v8::V8::InitializeExternalStartupData(engine.GetInfo().ExecutablePath.c_str());
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

    v8::Handle<v8::ObjectTemplate> engine = v8::ObjectTemplate::New(env->isolate);
    engine->Set(v8::String::NewFromUtf8(env->isolate, "loadGame", v8::NewStringType::kNormal).ToLocalChecked(),
      v8::FunctionTemplate::New(env->isolate, engineLoadGame));
    engine->Set(v8::String::NewFromUtf8(env->isolate, "loadAddin", v8::NewStringType::kNormal).ToLocalChecked(),
      v8::FunctionTemplate::New(env->isolate, engineLoadAddin));

    v8::Handle<v8::ObjectTemplate> game = v8::ObjectTemplate::New(env->isolate);

    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(env->isolate);
    global->Set(v8::String::NewFromUtf8(env->isolate, "engine", v8::NewStringType::kNormal).ToLocalChecked(), engine);
    global->Set(v8::String::NewFromUtf8(env->isolate, "game", v8::NewStringType::kNormal).ToLocalChecked(), game);

    v8::Handle<v8::ObjectTemplate> platformConfig = v8::ObjectTemplate::New(env->isolate);

  }

  return env;

}

Script * ScriptEnvironment::LoadScript(const string &filename) {
  return nullptr;
}

v8::Handle<v8::Value> ScriptEnvironment::RunScript(Script &script) {
  return v8::Handle<v8::Value>();
}

void ScriptEnvironment::engineLoadAddin(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Local<v8::Object> self = args.Holder();
  v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

  Engine *engine = (Engine *)wrap->Value();
  v8::String::Utf8Value filename(args[0]);
  engine->LoadAddin(*filename);

}

void ScriptEnvironment::engineLoadGame(const v8::FunctionCallbackInfo<v8::Value>& args) {

  v8::Local<v8::Object> self = args.Holder();
  v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

  Engine *engine = (Engine *)wrap->Value();
  v8::String::Utf8Value filename(args[0]);
  engine->LoadGame(*filename);

}
