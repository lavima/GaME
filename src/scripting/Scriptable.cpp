/*
File: Scriptable.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

namespace game::scripting {

    void _Scriptable::Register(ScriptEnvironment& environment) {
        this->environment = &environment;
    }

}