/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

extern "C" {

void RegisterAddin(AddinInfo &addinInfo);

EngineComponent *CreateEngineComponent(Engine &engine, const string &typeName, const string &name);

}