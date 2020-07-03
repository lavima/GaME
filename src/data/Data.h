/*
File: Data.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Data {
private:

    static unordered_map<string, DataLoader*>* data_loaders_;

    string filename_; 

protected:

    Data(const string& filename);

public:

    template<typename T> static T* Load(const string& filename);

    virtual bool Load() = 0;
    bool LoadFrom(const string& filename);

    const string &GetFilename();

protected:

    static void RegisterType(const string &extension, DataLoader* loader);

};

template<typename T> T *Data::Load(const string &filename) {

    if (!is_base_of<Data, T>::value)
        return nullptr;

    const string extension = FilePath::GetExtension(filename);
    if (data_loaders_->count(extension) == 0)
        return nullptr;

    return dynamic_cast<T *>(data_loaders_->at(extension)->Load(filename));

}

class WritableData : public Data {
protected:

    WritableData(const string &filename) : Data(filename) {}

public:

    virtual bool Save() = 0;

};
