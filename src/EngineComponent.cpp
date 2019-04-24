/*
File: EngineComponent.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

unordered_map<string, CreateEngineComponentFun> EngineComponent::componentProviders;

EngineComponent::EngineComponent(Engine &engine, const string &typeName) : __Instanceable(typeName) {

    this->engine = &engine;

}

EngineComponent *EngineComponent::Create(Engine &engine, const string &typeName) {

    unordered_map<string, CreateEngineComponentFun>::iterator item = componentProviders.find(typeName);
    if (item == componentProviders.end()) {
        printf("Could not find the specified game component type %s\n", typeName.c_str());
        return NULL;
    }

    CreateEngineComponentFun createEngineComponent = componentProviders[typeName];

    return createEngineComponent(engine, typeName);

}

void EngineComponent::RegisterProvider(const string &typeName, CreateEngineComponentFun createFun) { componentProviders[typeName] = createFun; }
