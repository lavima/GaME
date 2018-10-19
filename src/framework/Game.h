/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

typedef unordered_map<string, const string> EngineComponentsNeededMap;
typedef pair<string, const string> EngineComponentsNeededMapPair;
typedef EngineComponentsNeededMap::iterator EngineComponentsNeededMapIter;

struct GameInfo {

    int MajorVersion;
    int MinorVersion = 0;
    int Release = 1;

    string Name;

    const string &GetVersionString() { return StringUtil::Format("%d-%d-%d", MajorVersion, MinorVersion, Release); }

};

class Game {

private:

    GameInfo info;

    Script *gameScript;

    EngineComponentsNeededMap engineComponentsNeeded;

    Game() {}

public:

    static Game *Load(const string &filename);

    void Initialize();

    void LoadContent();
    void UnloadContent();

    void Update(GameTime &gameTime);

    const GameInfo &GetInfo();
    EngineComponentsNeededMap &GetEngineComponentsNeeded();

};