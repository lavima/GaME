/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::lib {

    class GAME_API FilePath {
    private:

        string filename_;
        string directory_;
        string extension_;

    public:

        FilePath(const string& filePath);

        static const string GetFilename(const string& filePath);
        const string& GetFilename() const;

        static const string GetDirectory(const string& filePath);
        const string& GetDirectory() const;

        static const string GetExtension(const string& file_path);
        const string& GetExtension() const;
    };

}