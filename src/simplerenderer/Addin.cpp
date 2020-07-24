/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace game::graphics::vulkan;

#include "Addin.h"
#include "Config.h"
#include "SimpleRenderer.h"

namespace game {

    void RegisterAddin(Engine& engine, AddinHeader& header) {

        // Initialize creator and loader singletons 

        simplerenderer::SimpleRenderer::Creator::Get();
        simplerenderer::Config::Loader::Get();

        engine.GetLog().AddEvent("Addin %s registered", header.GetName().c_str());

    }

    void UnregisterAddin(Engine& engine) {
    
        // TODO

    }
}