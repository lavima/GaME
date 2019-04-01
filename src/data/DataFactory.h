/*
File: Data.h
Author: Lars Vidar Magnusson
*/

#pragma once

template<typename T> class DataFactory {
public:
    virtual T *Load(const string &filename) = 0;
};
