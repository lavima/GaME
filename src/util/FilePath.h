/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

class FilePath {
private:

    string filename, directory;

public:

    FilePath(const string &filePath);

    static string GetFilename(const string &filePath);
    const string &GetFilename();

    static string GetDirectory(const string &filePath);
    const string &GetDirectory();

};