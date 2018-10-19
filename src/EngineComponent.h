/*
File: EngineComponent.h
Author: Lars Vidar Magnusson
*/

#pragma once

class EngineComponent;

typedef std::unordered_map<string, EngineComponent *> EngineComponentMap;
typedef std::pair<string, EngineComponentMap *> EngineComponentPair;
typedef EngineComponentMap::iterator EngineComponentMapIter;

typedef std::unordered_map<string, CreateEngineComponentFun> CreateEngineComponentMap;
typedef std::pair<string, CreateEngineComponentFun> CreateEngineComponentPair;
typedef CreateEngineComponentMap::iterator CreateEngineComponentMapIter;

class EngineComponent {

    friend class Engine;

private:

    Engine *engine;

    const string *typeName;
    const string *name;

    static CreateEngineComponentMap createEngineComponentMap;

protected:

    EngineComponent(Engine &engine);

public:

    static EngineComponent *Create(Engine &engine, const string &typeName, const string &name);

    const string &GetTypeName();
    const string &GetName();

    virtual void Initialize() = 0;
    virtual void Update(GameTime &gameTime) = 0;

};
