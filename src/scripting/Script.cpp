/*
File: Script.h
Author: Lars Vidar Magnusson
 */

#include <string>
#include <fstream>

#include <v8.h>

#include "../global.h"
#include "script_environment.h"
#include "script.h"

namespace game::scripting {

    Script::Script(const std::string& name) {
        this->name = name;
    }

    Script* Script::Load(ScriptEnvironment& environment, const std::string& filename) {

        std::ifstream file(filename, std::ios::in);

        if (!file)
            return nullptr;
        std::string source;
        file.seekg(0, std::ios::end);
        source.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&source[0], source.size());
        file.close();


        Script* newScript = new Script(filename);
        newScript->environment = &environment;

        v8::Context::Scope contextScope(environment.GetContext());
        //v8::HandleScope handleScope;                                                                                                                     
        //v8::TryCatch tryCatch;                                                                                                                           

        //v8::Handle<v8::String> nameString = v8::String::New(filename_);                                                                       
        //v8::Handle<v8::String> sourceString = v8::String::New(source);                                                                                   

        //v8::Handle<v8::Script> script = v8::Script::Compile(sourceString, nameString);                                                                   

        //if (script.IsEmpty()) {                                                                                                                          
        //    assert(tryCatch.HasCaught());                                                                                                                
        //    v8::V8::ReportException(&tryCatch);                                                                                                          
        //    return false;                                                                                                                                
        //}                                                                                                                                                

        //newScript->script = v8::Persistent<Script>::New(script);

        return newScript;

    }

    bool Script::Run() {

        v8::Context::Scope contextScope(environment->GetContext());
        //v8::HandleScope handleScope;
        //v8::TryCatch tryCatch;

        //v8::Handle<v8::Value> result = script->Start();

        //if (result.IsEmpty()) {
        //    assert(tryCatch.HasCaught());
        //    //ReportException(&tryCatch);
        //    return Handle<Value>();
        //}

        //Handle<Value> value = handleScope.Close(result);

        return true;

    }

    void Script::InvokeMethod(const std::string& methodName) {



    }

    const std::string& Script::GetName() { return name; }
    ScriptEnvironment& Script::GetEnvironment() { return *environment; }

}
