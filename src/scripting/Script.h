/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#ifndef __SCRIPTING_SCRIPT__
#define __SCRIPTING_SCRIPT__

class Script {

private:
  
  ScriptContext *context;
  const char *name;

  v8::Persistent<v8::Script> script;

  Script(const char *name) {
    this->name = name;
  }

public:

  static Script *Create(ScriptContext *context, const char *filename);
  
  const char *GetName() { return name; }

  bool Run();

  void InvokeMethod(const char *methodName);
  
  friend class ScriptUtil;
};

#endif
