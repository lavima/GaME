/*
File: ScriptContext.cpp
Author: Lars Vidar Magnusson
*/

#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "../lib/CStringHash.h"
#include "../platform/PlatformConfig.h"
#include "../platform/Platform.h"
#include "ScriptContext.h"
#include "Script.h"
#include "../framework/GameTime.h"
#include "../framework/GameComponent.h"
#include "../framework/Game.h"
#include "../AddinInfo.h"
#include "../AddinContainer.h"
#include "../Addin.h"
#include "../EngineConfig.h"
#include "../Engine.h"

v8::Handle<v8::Value> EngineLoadAddin(const v8::Arguments &args);
v8::Handle<v8::Value> EngineRunGame(const v8::Arguments &args);

ScriptContext::~ScriptContext() {
  
  scriptContext->Exit();
  scriptContext.Dispose();

}

ScriptContext *ScriptContext::Create() {

  v8::HandleScope handleScope;
  
  v8::Handle<v8::ObjectTemplate> globalTemplate = v8::ObjectTemplate::New();
  globalTemplate->SetInternalFieldCount(1);

  ScriptContext *newContext = new ScriptContext();
  newContext->scriptContext = v8::Context::New(NULL, globalTemplate);

  newContext->scriptContext->Enter();

  v8::Handle<v8::Object> globalObject = 
    v8::Handle<v8::Object>::Cast(newContext->scriptContext->Global()->GetPrototype());
  globalObject->SetInternalField(0, v8::External::New(newContext));

  // Create the platform config template

  newContext->platformConfigTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
  newContext->platformConfigTemplate->SetInternalFieldCount(1);

  // Create the engine template

  newContext->engineTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
  newContext->engineTemplate->SetInternalFieldCount(1);
  newContext->engineTemplate->Set(v8::String::New("loadAddin"), v8::FunctionTemplate::New(EngineLoadAddin));
  newContext->engineTemplate->Set(v8::String::New("loadGame"), v8::FunctionTemplate::New(EngineRunGame));

  // Create the game template

  newContext->gameTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New()); 
  newContext->gameTemplate->SetInternalFieldCount(1);

  v8::Handle<v8::Object> engineObject = newContext->engineTemplate->NewInstance();
  engineObject->SetInternalField(0, v8::External::New(ENGINE));

  globalObject->Set(v8::String::New("engine"), engineObject);

  return newContext;

}

v8::Handle<v8::Value> EngineLoadAddin(const v8::Arguments &args) {

  v8::Local<v8::Object> self = args.Holder();
  v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

  Engine *engine = (Engine *)wrap->Value();
  v8::String::Utf8Value filename(args[0]);
  engine->LoadAddin(*filename);

  return v8::Undefined();

}

v8::Handle<v8::Value> EngineRunGame(const v8::Arguments &args) {

  v8::Local<v8::Object> self = args.Holder();
  v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));

  Engine *engine = (Engine *)wrap->Value();
  v8::String::Utf8Value filename(args[0]);
  engine->RunGame(*filename);

  return v8::Undefined();

}
