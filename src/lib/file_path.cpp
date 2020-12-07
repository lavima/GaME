/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#include <string>

#include "../global.h"
#include "file_path.h"

namespace game::lib {

    FilePath::FilePath(const std::string& file_path) {

        size_t last = file_path.find_last_of("/\\", 0);

        filename_ = file_path.substr(last+1);
        directory_ = file_path.substr(0, last);
        extension_ = file_path.substr(file_path.find_last_of('.')+1);

    }

    const std::string FilePath::GetFilename(const std::string& file_path) {

        size_t last = file_path.find_last_of("/\\", 0);
        return file_path.substr(last+1);

    }

    const std::string& FilePath::GetFilename() const {
        return filename_;
    }

    const std::string FilePath::GetDirectory(const std::string& file_path) {

        size_t last = file_path.find_last_of("/\\", 0);
        return file_path.substr(0, last);

    }

    const std::string& FilePath::GetDirectory() const {
        return directory_;
    }

    const std::string FilePath::GetExtension(const std::string& file_path) {
        return file_path.substr(file_path.find_last_of('.')+1);
    }

    const std::string& FilePath::GetExtension() const {
        return extension_;
    }

}
