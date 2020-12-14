/*
File: Scriptable.cpp
Author: Lars Vidar Magnusson
*/

#include <string>

#include <v8.h>

#include "../global.h"
#include "script_environment.h"
#include "scriptable.h"

namespace game::scripting {

    void _Scriptable::Register(ScriptEnvironment& environment) {
        this->environment = &environment;
    }

}
