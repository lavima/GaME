/*
File: Scriptable.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

void _Scriptable::Register(ScriptEnvironment &environment) {
    this->environment = &environment;
}
