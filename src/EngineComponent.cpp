/*
File: EngineComponent.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

unordered_map<string, CreateEngineComponentFun> EngineComponent::createEngineComponentMap;

EngineComponent::EngineComponent(Engine &engine) {

    this->engine = &engine;

}

EngineComponent *EngineComponent::Create(Engine &engine, const string &typeName, const string &name) {

    unordered_map<string, CreateEngineComponentFun>::iterator item = createEngineComponentMap.find(typeName);
    if (item == createEngineComponentMap.end()) {
        printf("Could not find the specified game component type %s\n", typeName.c_str());
        return NULL;
    }

    CreateEngineComponentFun createEngineComponent = createEngineComponentMap[typeName];

    return createEngineComponent(engine, typeName, name);

}

const string &EngineComponent::GetTypeName() { return this->typeName; }
const string &EngineComponent::GetName() { return this->name; }
