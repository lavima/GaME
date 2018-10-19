/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

#include "SimpleRendererAddin.h"
#include "SimpleRenderer.h"


void RegisterAddin(AddinInfo &addinInfo) {
  
  printf("Addin %s\n", addinInfo.GetName().c_str());

}

EngineComponent *CreateEngineComponent(Engine &engine, const string &typeName, const string &name) {

  return new SimpleRenderer(engine);

}
