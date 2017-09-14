/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;
class EngineComponent;

typedef void (*RegisterAddinFun)(AddinInfo &);
typedef EngineComponent *(*CreateEngineComponentFun)(Engine &, const string &, const string &);

#define ADDIN_REGISTERADDIN "RegisterAddin"
#define ADDIN_CREATECOMPONENT "CreateEngineComponent"