/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#include <string>

#include "FilePath.h"

FilePath::FilePath(const string &filePath) {

    size_t last = filename.find_last_of("/\\", 0);

    this->filename = filename.substr(last + 1);
    this->directory = filename.substr(0, last);

}

string FilePath::GetFilename(const string &filePath) {

    size_t last = filePath.find_last_of("/\\", 0);
    return filePath.substr(last + 1);

}

string FilePath::GetDirectory(const string &filePath) {

    size_t last = filePath.find_last_of("/\\", 0);
    return filePath.substr(0, last);

}