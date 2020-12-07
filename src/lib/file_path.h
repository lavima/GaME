/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::lib {

    class GAME_API FilePath {
    private:

        std::string filename_;
        std::string directory_;
        std::string extension_;

    public:

        FilePath(const std::string& filePath);

        static const std::string GetFilename(const std::string& filePath);
        const std::string& GetFilename() const;

        static const std::string GetDirectory(const std::string& filePath);
        const std::string& GetDirectory() const;

        static const std::string GetExtension(const std::string& file_path);
        const std::string& GetExtension() const;
    };

}