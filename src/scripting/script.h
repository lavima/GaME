/*
File: Script.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::scripting {

    class GAME_API Script {

    private:

        ScriptEnvironment* environment;
        std::string name;

        //v8::Persistent<v8::Script>* script;

        Script(const std::string& name);

    public:

        static Script* Load(ScriptEnvironment& environment, const std::string& filename);

        bool Run();

        void InvokeMethod(const std::string& methodName);

        const std::string& GetName();
        ScriptEnvironment& GetEnvironment();

    };

}