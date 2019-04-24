/*
File: EngineComponent.h
Author: Lars Vidar Magnusson
*/

#pragma once

class EngineComponent;

typedef EngineComponent *(*CreateEngineComponentFun)(Engine &, const string &);
#define ADDINFUN_ENGINECOMPONENT_CREATE "CreateEngineComponent"

class EngineComponent : public __Instanceable {
private:

    Engine *engine;

    static unordered_map<string, CreateEngineComponentFun> componentProviders;

protected:

    EngineComponent(Engine &engine, const string &typeName);

public:

    static EngineComponent *Create(Engine &engine, const string &typeName);
    static void RegisterProvider(const string &typeName, CreateEngineComponentFun createFun);

    virtual void Initialize() = 0;
    virtual void Update(GameTime &gameTime) = 0;

};
