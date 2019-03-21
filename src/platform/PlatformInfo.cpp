/*
File: PlatformInfo.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

PlatformInfo::PlatformInfo(PlatformType type, const string &name, const string &description, const Version &version)
    : _InfoBase(name, description, version) {

    this->type = type;

}
