/*
File: Script.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace GaME {

class Script {

private:

    ScriptEnvironment *environment;
    const std::string name;

    v8::Persistent<v8::Script> *script;

    Script(const string &name); 

public:

    static Script *Load(ScriptEnvironment &environment, const std::string &filename);

    bool Run();

    void InvokeMethod(const std::string &methodName);

    const string &GetName();
    ScriptEnvironment &GetEnvironment();

};

}
