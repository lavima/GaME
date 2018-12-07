/*
File: Platform.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"


Platform *Platform::Create(PlatformConfig *config) {

    if (!implementations.count(config->GetTypeName()))
        return nullptr;
    
    CreatePlatformFun createPlatform;
    createPlatform = implementations[config->GetTypeName()];
    
    return createPlatform(config);

}

void Platform::RegisterImplementation(const string &name, CreatePlatformFun createFun) {

    implementations[name] = createFun;

}

unordered_map<string, CreatePlatformFun> Platform::implementations;
