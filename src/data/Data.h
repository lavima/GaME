/*
File: Data.h
Author: Lars Vidar Magnusson
*/

#pragma once

template<typename T> class Data {
private:

    static unordered_map<string, DataFactory<T> *> datatypes;

    string filename; 

protected:

    Data(const string &filename);

public:

    static T *Load(const string &filename);

    virtual bool Load() = 0;
    bool LoadFrom(const string &filename);

    const string &GetFilename();

protected:

    static void RegisterType(const string &extension);

};

template<typename T> class WritableData : Data<T> {
protected:

    WritableData<T>(const string &filename) : Data<T>(filename) {}

public:

    virtual bool Save() = 0;

};
