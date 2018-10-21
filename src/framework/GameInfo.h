/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/


#pragma once

typedef unordered_map<string, const string *> EngineComponentNameMap;
typedef pair<string, const string *> EngineComponentNamePair;
typedef EngineComponentNameMap::iterator EngineComponentNameIter;
typedef EngineComponentNameMap::const_iterator EngineComponentNameConstIter;

class GameInfo {
private:
    
    const string *filename;

    const string *name;
    const string *description;
    const Version *version;

    EngineComponentNameMap engineComponents;

    GameInfo() {}

public:

    ~GameInfo();

    static GameInfo *Load(const string &filename);

    const string &GetName() const;
    const string &GetDescription() const;
    const Version &GetVersion() const;
    const EngineComponentNameMap &GetEngineComponents() const;

};