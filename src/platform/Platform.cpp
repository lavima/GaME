/*
File: Platform.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

unordered_map<string, CreatePlatformFun> Platform::implementations;


Platform *Platform::Create(Engine &engine, PlatformConfig *config) {

    if (!implementations.count(config->GetTypeName()))
        return nullptr;
    
    CreatePlatformFun createPlatform;
    createPlatform = implementations[config->GetTypeName()];
    
    return createPlatform(engine, config);

}

const unordered_map<KeyCode, reference_wrapper<const InputKey>> GraphicalPlatform::GetInputKeys() {
    return unordered_map<KeyCode, reference_wrapper<const InputKey>>(inputKeys.begin(), inputKeys.end()); 
}

void Platform::RegisterImplementation(const string &name, CreatePlatformFun createFun) {

    implementations[name] = createFun;

}

Engine &Platform::GetEngine() { return engine; }
unordered_map<KeyCode, __InputKeyWritable> __GraphicalPlatformInternal::GetWritableInputKeys() { return inputKeys; }
