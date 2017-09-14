/*
File: Script.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"
  
Script *Script::Create(ScriptEnvironment &context, const string &filename) {
  
  ifstream file(filename, ios::in);

  if (!file) 
    return nullptr;
  string source;
  file.seekg(0, std::ios::end);
  source.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&source[0], source.size());
  file.close();


  Script *newScript = new Script(filename);
  newScript->context = &context;

  
  return newScript;  
}

bool Script::Run() {

  return true;
}

void Script::InvokeMethod(const string &methodName) {

  

}

