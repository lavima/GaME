/*
File: Data.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Data {
private:

    static unordered_map<string, DataFactory *> datatypes;

    string filename; 

protected:

    Data(const string &filename);

public:

    template<typename T> static T *Load(const string &filename);

    virtual bool Load() = 0;
    bool LoadFrom(const string &filename);

    const string &GetFilename();

protected:

    static void RegisterType(const string &extension, DataFactory *factory);

};

template<typename T> T *Data::Load(const string &filename) {

    if (!is_base_of<Data, T>::value)
        return nullptr;
    if (datatypes.count(filename) == 0)
        return nullptr;

    return dynamic_cast<T *>(datatypes[filename]->Load(filename));

}

class WritableData : public Data {
protected:

    WritableData(const string &filename) : Data(filename) {}

public:

    virtual bool Save() = 0;

};
