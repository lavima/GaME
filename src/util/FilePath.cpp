/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#include <string>

using namespace std;

#include "FilePath.h"

FilePath::FilePath(const string &file_path) {

    size_t last = file_path.find_last_of("/\\", 0);

    filename_ = file_path.substr(last + 1);
    directory_ = file_path.substr(0, last);
    extension_ = file_path.substr(file_path.find_last_of('.')+1);

}

const string FilePath::GetFilename(const string &file_path) {

    size_t last = file_path.find_last_of("/\\", 0);
    return file_path.substr(last + 1);

}

const string& FilePath::GetFilename() const {
    return filename_;
}

const string FilePath::GetDirectory(const string &file_path) {

    size_t last = file_path.find_last_of("/\\", 0);
    return file_path.substr(0, last);

}

const string& FilePath::GetDirectory() const {
    return directory_;
}

const string FilePath::GetExtension(const string& file_path) {
    return file_path.substr(file_path.find_last_of('.')+1);
}

const string& FilePath::GetExtension() const {
    return extension_;
}
