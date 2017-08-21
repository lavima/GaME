/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Script {

private:
  
  ScriptEnvironment *context;
  const char *name;

  v8::Persistent<v8::Script> script;

  Script(const char *name) {
    this->name = name;
  }

public:

  static Script *Create(ScriptEnvironment *context, const char *filename);
  
  const char *GetName() { return name; }

  bool Run();

  void InvokeMethod(const char *methodName);
  
};