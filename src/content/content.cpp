/*
File: Content.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <unordered_map>

#include <pugixml.hpp>

#include "../global.h"
#include "Content.h"

namespace game::content {

    // 
    // Declare the static member pointer. The creation of the object uses a First Use idiom 
    // to avoid static fiasco.
    //
    std::unordered_map<std::string, Content::ILoader*>* Content::data_loaders_ = nullptr;

    Content::Content(const std::string& filename) {
        this->filename_ = filename;
    }

    bool Content::LoadFrom(const std::string& filename) {

        this->filename_ = filename;
        return Load();

    }

    const std::string& Content::GetFilename() { return filename_; }

    void Content::RegisterType(const std::string& extension, Content::ILoader* loader) {

        // Load the map to store the loaders if it doesn't already exist. This memory is
        // cleared by the OS on exit
        if (!data_loaders_)
            data_loaders_ = new std::unordered_map<std::string, Content::ILoader*>();

        data_loaders_->insert_or_assign(extension, loader);

    }

    void Content::RegisterTypes(const std::vector<std::string>& extensions, ILoader* loader) {
        for (const auto extension:extensions)
            RegisterType(extension, loader);
    }

}
