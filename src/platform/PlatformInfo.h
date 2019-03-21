/*
File: PlatformInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum PlatformType {
    PLATFORMTYPE_CONSOLE,
    PLATFORMTYPE_GRAPHICAL
};

class PlatformInfo : public _InfoBase {

private:
    
    PlatformType type;
    
public:
    
    PlatformInfo(PlatformType type, const string &name, const string &description, const Version &version);

};
