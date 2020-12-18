/*
File: FilePath.h
Author: Lars Vidar Magnusson
*/

// TODO Replace all uses of this with std::filesystem::path

#pragma once

namespace game::lib {

		/*
		* FilePath provides similar functionality to std::filesystem::path which
		* seems to be lacking support in libc++ (at least in windows). So for now,
		* this class is still relevant.
		* TODO Rename to Path? 	
		*/
    class GAME_API FilePath {
    private:

        std::string filename_;
        std::string directory_;
        std::string extension_;

    public:

        FilePath(const std::string& filePath);

        static const std::string filename(const std::string& filePath);
        const std::string& filename() const;

        static const std::string directory(const std::string& filePath);
        const std::string& directory() const;

        static const std::string extension(const std::string& file_path);
        const std::string& extension() const;

    };

}
