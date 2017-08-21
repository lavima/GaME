/*
File: ScriptUtil.cpp
Author: Lars Vidar Magnusson
*/

#include <assert.h>
#include <string.h>
#include <v8.h>

#include <unordered_map>

#include "../lib/CStringHash.h"
#include "ScriptContext.h"
#include "Script.h"
#include "../framework/GameTime.h"
#include "../framework/GameComponent.h"
#include "../framework/Game.h"
#include "ScriptUtil.h"

bool ScriptUtil::Compile(Script *gameScript, const char *source) {

  v8::Context::Scope contextScope(gameScript->context->scriptContext);
  v8::HandleScope handleScope;
  v8::TryCatch tryCatch;

  v8::Handle<v8::String> nameString = v8::String::New(gameScript->GetName());
  v8::Handle<v8::String> sourceString = v8::String::New(source);

  v8::Handle<v8::Script> script = v8::Script::Compile(sourceString, nameString);

  if (script.IsEmpty()) {
    assert(tryCatch.HasCaught());
    ReportException(&tryCatch);
    return false;
  }

  gameScript->script = v8::Persistent<v8::Script>::New(script);

  return true;
}

v8::Handle<v8::Value> ScriptUtil::Run(Script *gameScript) {

  v8::Context::Scope contextScope(gameScript->context->scriptContext);
  v8::HandleScope handleScope;
  v8::TryCatch tryCatch;

  v8::Handle<v8::Value> result = gameScript->script->Run();

  if (result.IsEmpty()) {
    assert(tryCatch.HasCaught());
    ScriptUtil::ReportException(&tryCatch);
    return v8::Handle<v8::Value>();
  }

  return handleScope.Close(result);
}

void ScriptUtil::ReportException(v8::TryCatch *tryCatch) {

  v8::HandleScope handleScope;

  v8::String::Utf8Value exception(tryCatch->Exception());
  const char* exceptionString = ToCString(exception);
  
  v8::Handle<v8::Message> message = tryCatch->Message();
  
  if (!message.IsEmpty()) {
    
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filenameString = ToCString(filename);
    
    int linenum = message->GetLineNumber();
    printf("%s:%i: %s\n", filenameString, linenum, exceptionString);
    
    v8::String::Utf8Value stackTrace(tryCatch->StackTrace());
    if (stackTrace.length() > 0) {
      const char* stackTraceString = ToCString(stackTrace);
      printf("%s\n", stackTraceString);
    }
  }
  else
    printf("%s\n", exceptionString);
}

const char *ScriptUtil::ToCString(const v8::String::Utf8Value &value) {
  return *value ? *value : "Failed to convert to string";
}
