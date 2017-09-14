/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Script {

private:
  
  ScriptEnvironment *context;
  const std::string *name;

  v8::Persistent<v8::Script> *script;

  Script(const std::string &name) {
    this->name = &name;
  }

public:

  static Script *Create(ScriptEnvironment &context, const std::string &filename);
  
  const std::string &GetName() { return *name; }

  bool Run();

  void InvokeMethod(const std::string &methodName);
  
};