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
        extension_ = file_path.substr(file_path.find_last_of('.'));

    }

    const std::string FilePath::filename(const std::string& file_path) {

        size_t last = file_path.find_last_of("/\\", 0);
        if (last==std::string::npos)
            return file_path;
        return file_path.substr(last+1);

    }

    const std::string& FilePath::filename() const {
        return filename_;
    }

    const std::string FilePath::directory(const std::string& file_path) {

        size_t last = file_path.find_last_of("/\\", 0);
        return file_path.substr(0, last);

    }

    const std::string& FilePath::directory() const {
        return directory_;
    }

    const std::string FilePath::extension(const std::string& file_path) {
        return file_path.substr(file_path.find_last_of('.'));
    }

    const std::string& FilePath::extension() const {
        return extension_;
    }

}
