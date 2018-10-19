/*
File: Platform.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include "PlatformConfig.h"
#include "Platform.h"


Platform *Platform::Create(PlatformConfig &config) {

    if (!implementations.count(config.GetTypeName()))
        return nullptr;
    
    CreatePlatformFun createPlatform;
    createPlatform = implementations[config.GetTypeName()];
    
    return createPlatform(config);

}

void Platform::RegisterImplementation(const string &typeName, CreatePlatformFun createFun) {

    implementations[typeName] = createFun;

}

CreatePlatformMap Platform::implementations;