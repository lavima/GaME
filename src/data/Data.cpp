/*
File: Data.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

namespace game::data {

    // 
    // Declare the static member pointer. The creation of the object uses a First Use idiom 
    // to avoid static fiasco.
    //
    unordered_map<string, Data::ILoader*>* Data::data_loaders_ = nullptr;

    Data::Data(const string& filename) {
        this->filename_ = filename;
    }

    bool Data::LoadFrom(const string& filename) {

        this->filename_ = filename;
        return Load();

    }

    const string& Data::GetFilename() { return filename_; }

    void Data::RegisterType(const string& extension, Data::ILoader* loader) {

        // Load the map to store the loaders if it doesn't already exist. This memory is
        // cleared by the OS on exit
        if (!data_loaders_)
            data_loaders_ = new unordered_map<string, Data::ILoader*>();

        data_loaders_->insert_or_assign(extension, loader);

    }

    void Data::RegisterTypes(const vector<string>& extensions, ILoader* loader) {
        for (const auto extension:extensions)
            RegisterType(extension, loader);
    }

}