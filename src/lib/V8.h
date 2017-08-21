/*
File: ScriptUtil.h
Author: Lars Vidar Magnusson
*/

#ifndef __SCRIPTING_SCRIPTUTIL__
#define __SCRIPTING_SCRIPTUTIL__

class ScriptUtil {

public:

  static bool Compile(Script *gameScript, const char *source);
  static v8::Handle<v8::Value> Run(Script *gameScript);
  static void ReportException(v8::TryCatch *tryCatch);
  static const char *ToCString(const v8::String::Utf8Value &value);

};

#endif
