/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <unordered_map>

#include <v8.h>

#include "../lib/CStringHash.h"
#include "ScriptContext.h"
#include "Script.h"
#include "../framework/GameTime.h"
#include "../framework/GameComponent.h"
#include "../framework/Game.h"
#include "ScriptUtil.h"
  
Script *Script::Create(ScriptContext *context, const char *filename) {
  
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return NULL;

  fseek(file, 0, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *sourceBuffer = new char[fileSize + 1];
  int numCharsRead = fread(sourceBuffer, 1, fileSize, file);

  assert(numCharsRead == fileSize);

  sourceBuffer[numCharsRead] = '\0';

  Script *newScript = new Script(filename);
  newScript->context = context;

  if (!ScriptUtil::Compile(newScript, sourceBuffer))
    return NULL;
  
  return newScript;  
}

bool Script::Run() {

  v8::HandleScope handleScope;

  v8::String::Utf8Value retString(ScriptUtil::Run(this));
  printf("%s\n", ScriptUtil::ToCString(retString));

  return true;
}

void Script::InvokeMethod(const char *methodName) {

  

}

