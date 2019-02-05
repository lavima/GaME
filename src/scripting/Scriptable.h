/*
File: Scriptable.h
Author: Lars Vidar Magnusson
*/

#pragma once

class _Scriptable {

protected:

    ScriptEnvironment *environment;

public:

    virtual void Register(ScriptEnvironment &environment);

};
