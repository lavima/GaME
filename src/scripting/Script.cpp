/*
File: Script.h
Author: Lars Vidar Magnusson
 */

#include "../GaME.h"

namespace game::scripting {

    Script::Script(const string& name) {
        this->name = name;
    }

    Script* Script::Load(ScriptEnvironment& environment, const string& filename) {

        ifstream file(filename, ios::in);

        if (!file)
            return nullptr;
        string source;
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

    void Script::InvokeMethod(const string& methodName) {



    }

    const string& Script::GetName() { return name; }
    ScriptEnvironment& Script::GetEnvironment() { return *environment; }

}