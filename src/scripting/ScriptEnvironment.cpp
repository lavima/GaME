/*
File: ScriptContext.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"


ScriptEnvironment::~ScriptEnvironment() {
  
  isolate->Dispose();
  delete allocator;

}

ScriptEnvironment *ScriptEnvironment::Create(Engine &engine) {

  ScriptEnvironment *newEnvironment = new ScriptEnvironment();
  newEnvironment->engine = &engine;
  newEnvironment->allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

  v8::Isolate::CreateParams createParams;
  createParams.array_buffer_allocator = newEnvironment->allocator;

  v8::Isolate *isolate = newEnvironment->isolate = v8::Isolate::New(createParams);
  {

    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope handleScope(isolate);

    v8::Handle<v8::ObjectTemplate> engine = v8::ObjectTemplate::New();
    engine->Set(v8::String::NewFromUtf8(isolate, "loadGame", v8::NewStringType::kNormal).ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, engineLoadGame));
    engine->Set(v8::String::NewFromUtf8(isolate, "loadAddin", v8::NewStringType::kNormal).ToLocalChecked(),
      v8::FunctionTemplate::New(isolate, engineLoadAddin));

    v8::Handle<v8::ObjectTemplate> game = v8::ObjectTemplate::New();

    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
    global->Set(v8::String::NewFromUtf8(isolate, "engine", v8::NewStringType::kNormal).ToLocalChecked(), engine);
    global->Set(v8::String::NewFromUtf8(isolate, "game", v8::NewStringType::kNormal).ToLocalChecked(), game);

    v8::Handle<v8::ObjectTemplate> platformConfig = v8::ObjectTemplate::New();

  }

  return newEnvironment;

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
