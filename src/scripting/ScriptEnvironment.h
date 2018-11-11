/*
File: ScriptContext.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;
class Script;

class ScriptEnvironment {
private:

  Engine *engine;

  v8::Isolate *isolate;
  v8::ArrayBuffer::Allocator *allocator;

  v8::UniquePersistent<v8::Context> *globalContext;

  ScriptEnvironment(Engine &engine);

  static void engineLoadAddin(const v8::FunctionCallbackInfo<v8::Value>&);
  static void engineLoadGame(const v8::FunctionCallbackInfo<v8::Value>&);
  
public:

  ~ScriptEnvironment();

  static ScriptEnvironment *Load(Engine &);

  Script *LoadScript(const std::string &);
  v8::Handle<v8::Value> RunScript(Script &);

};