/*
File: Data.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

unordered_map<string, DataFactory<T> *> Data<T>::datatypes;

Data<T>::Data(const string &filename) {
    this->filename = filename;
}

T *Data::Load(const string &filename) {

    if (datatypes[filename].count == 0)
        return nullptr;

    return datatypes[filename]->Load(filename);

}

bool Data::LoadFrom(const string &filename) {

    this->filename = filename;
    return Load();

}

const string &Data::GetFilename() { return filename; }
