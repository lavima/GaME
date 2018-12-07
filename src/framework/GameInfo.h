/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

class GameInfo : public _InfoBase {
private:
    
    vector<string> requiredAddins;

    GameInfo() {}

public:

    GameInfo(pugi::xml_node &xmlNode);
    ~GameInfo();


    const vector<string> &GetRequiredAddins() const;

};
