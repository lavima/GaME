/*
File: ScriptContext.h
Author: Lars Vidar Magnusson
*/

#ifndef __SCRIPTING_SCRIPTCONTEXT__
#define __SCRIPTING_SCRIPTCONTEXT__

class ScriptContext {

private:

  v8::Persistent<v8::Context> scriptContext;

  v8::Persistent<v8::ObjectTemplate> platformConfigTemplate;
  v8::Persistent<v8::ObjectTemplate> engineTemplate;
  v8::Persistent<v8::ObjectTemplate> gameTemplate;

public:

  ~ScriptContext();

  static ScriptContext *Create();

  friend class ScriptUtil;

};

#endif

