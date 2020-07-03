/*
File: SimpleRendererAddin.h
Author: Lars Vidar Magnusson
*/

#pragma once

extern "C" {

void RegisterAddin(AddinHeader &addinInfo);

EngineComponent *CreateEngineComponent(Engine &engine, const string &typeName, const string &name);

}
