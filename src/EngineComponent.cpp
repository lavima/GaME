/*
File: EngineComponent.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

unordered_map<string, CreateEngineComponentFun> EngineComponent::component_providers_;

EngineComponent::EngineComponent(Engine &engine, EngineComponentConfig& config) {

    engine_ = &engine;
    config_ = &config;

}

Engine& EngineComponent::GetEngine() {
    return *engine_;
}

EngineComponentConfig& EngineComponent::GetConfig() {
    return *config_;
}

EngineComponent *EngineComponent::Create(Engine &engine, EngineComponentConfig& config) {

    unordered_map<string, CreateEngineComponentFun>::iterator item = component_providers_.find(config.GetTypeName());
    if (item == component_providers_.end()) {
        engine.GetLog().AddEvent(EventType::Error, "Could not find the specified game component type %s", config.GetTypeName());
        return NULL;
    }

    CreateEngineComponentFun createEngineComponent = component_providers_[config.GetTypeName()];

    return createEngineComponent(engine, config);

}

void EngineComponent::RegisterProvider(const string &typeName, CreateEngineComponentFun createFun) { 
    
    component_providers_.insert_or_assign(typeName, createFun); 

}
