/*
File: Scriptable.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::scripting {

    class GAME_API _Scriptable {

    protected:

        ScriptEnvironment* environment;

    public:

        virtual void Register(ScriptEnvironment& environment);

    };

}