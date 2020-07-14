/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include <vulkan/vulkan.h>

#include "../GaME.h"

#include "SimpleRendererAddin.h"
#include "SimpleRenderer.h"


void RegisterAddin(Engine& engine, AddinHeader& addinInfo) {

    engine.GetLog().AddEvent("Addin %s registered", addinInfo.GetName().c_str());

}

EngineComponentConfig* LoadEngineComponentConfig(XmlNode root_node) {
    return new EngineComponentConfig(root_node);
}

bool SaveEngineComponentConfig(EngineComponentConfig& config, XmlNode root_node) {
    return false;
}

EngineComponent* CreateEngineComponent(Engine& engine, EngineComponentConfig& config) {

    return new SimpleRenderer(engine, config);

}
