/*
File: SimpleRendererAddin.h
Author: Lars Vidar Magnusson
*/

#pragma once

extern "C" {

__declspec(dllexport) void RegisterAddin(Engine& engine, AddinHeader &addinInfo);

__declspec(dllexport) EngineComponent* CreateEngineComponent(Engine &engine, EngineComponentConfig& config);

__declspec(dllexport) EngineComponentConfig* LoadEngineComponentConfig(XmlNode root_node);

__declspec(dllexport) bool SaveEngineComponentConfig(EngineComponentConfig& config, XmlNode root_node);

}
