/*
File: EngineComponent.h
Author: Lars Vidar Magnusson
*/

#pragma once

class EngineComponent {

    friend class Engine;

private:

    Engine *engine;

    const string typeName;
    const string name;

    static unordered_map<string, CreateEngineComponentFun> createEngineComponentMap;

protected:

    EngineComponent(Engine &engine);

public:

    static EngineComponent *Create(Engine &engine, const string &typeName, const string &name);

    const string &GetTypeName();
    const string &GetName();

    virtual void Initialize() = 0;
    virtual void Update(GameTime &gameTime) = 0;

};
