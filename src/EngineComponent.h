/*
File: EngineComponent.h
Author: Lars Vidar Magnusson
*/

#pragma once

class EngineComponent;

typedef std::unordered_map<const char *, EngineComponent *, CStringHash, CStringCompare> EngineComponentMap;
typedef std::pair<const char *, EngineComponentMap *> EngineComponentPair;
typedef EngineComponentMap::iterator EngineComponentMapIter;

typedef std::unordered_map<const char *, CreateEngineComponentFun, CStringHash, CStringCompare> CreateEngineComponentMap;
typedef std::pair<const char *, CreateEngineComponentFun> CreateEngineComponentPair;
typedef CreateEngineComponentMap::iterator CreateEngineComponentMapIter;

class EngineComponent {

  friend class Engine;

private:

  const char *typeName;
  const char *name;

  static CreateEngineComponentMap createEngineComponentMap;

protected:

  EngineComponent() {}

public:

  static EngineComponent *Create(const char *typeName, const char *name);

  const char *GetName();

  virtual void Initialize() = 0;
  virtual void Update(GameTime *gameTime) = 0;

};
