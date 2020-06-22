/*
File: Data.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Data;

class DataFactory {
public:
    virtual Data *Load(const string &filename) = 0;
};
