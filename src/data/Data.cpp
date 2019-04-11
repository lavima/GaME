/*
File: Data.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

unordered_map<string, DataFactory *> Data::datatypes;

Data::Data(const string &filename) {
    this->filename = filename;
}

bool Data::LoadFrom(const string &filename) {

    this->filename = filename;
    return Load();

}

const string &Data::GetFilename() { return filename; }

void Data::RegisterType(const string &extension, DataFactory *factory) {

}
