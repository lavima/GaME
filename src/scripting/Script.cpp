/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <unordered_map>

#include <v8.h>

#include "../lib/CommonTypes.h"
#include "../lib/CStringHash.h"
#include "ScriptEnvironment.h"
#include "Script.h"
#include "../framework/GameTime.h"
#include "../framework/Game.h"
  
Script *Script::Create(ScriptEnvironment *context, const char *filename) {
  
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

  
  return newScript;  
}

bool Script::Run() {



  return true;
}

void Script::InvokeMethod(const char *methodName) {

  

}

