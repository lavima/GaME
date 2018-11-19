/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/


#pragma once

class GameInfo : public _InfoBase {
private:
    
    const string *filename;
    StringVector engineComponents;

    GameInfo() {}

public:

    ~GameInfo();

    static GameInfo *Load(const string &filename);

    const string &GetFilename() const;
    const StringVector &GetEngineComponents() const;

};
