/*
File: EngineComponent.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

CreateEngineComponentMap EngineComponent::createEngineComponentMap;

EngineComponent::EngineComponent(Engine &engine) {

    this->engine = &engine;

}

EngineComponent *EngineComponent::Create(Engine &engine, const string &typeName, const string &name) {

  CreateEngineComponentMapIter item = createEngineComponentMap.find(typeName);
  if (item == createEngineComponentMap.end()) {
    printf("Could not find the specified game component type %s\n", typeName);
    return NULL;
  }
  CreateEngineComponentFun createEngineComponent = createEngineComponentMap[typeName];
  return createEngineComponent(engine, typeName, name);

}

const string & EngineComponent::GetTypeName() { return *(this->name); }
const string & EngineComponent::GetName() { return *(this->name); }
