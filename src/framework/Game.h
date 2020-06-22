/*
File: Game.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace pugi;

#define EXTENSION_GAME "game"

#define XMLNAME_GAME "Game"
#define XMLNAME_GAME_INFO XMLNAME_GAMEINFO
#define XMLNAME_GAME_CONFIG XMLNAME_GAMECONFIG

class Game : public XMLData {

private:

    Engine *engine;

    unique_ptr<GameInfo> info;
    unique_ptr<GameConfig> config;

    unique_ptr<Script> gameScript;

public:

    Game(const string &filename) : XMLData(filename) {}

    void Initialize(Engine &engine);

    void LoadContent();
    void UnloadContent();

    void Update(GameTime &gameTime);

    const GameInfo &GetInfo();
    GameConfig &GetConfig();

    bool Load(pugi::xml_node rootNode);
    bool Save(pugi::xml_node rootNode);

	using XMLData::Load;
	using XMLData::Save;

private:
    
    class __Factory : DataFactory {
    private:

        static __Factory singleton;

        __Factory();

    public:

        Data *Load(const string &filename);

    };

};
