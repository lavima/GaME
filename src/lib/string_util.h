/*
File: string_util.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::lib {

    class GAME_API StringUtil {
    public:

        template <typename ... T> inline static std::string* Format(const std::string& format, T ... args) {

            size_t size = snprintf(nullptr, 0, format.c_str(), args ...)+1;
            std::unique_ptr<char[]> buffer(new char[size]);
            snprintf(buffer.get(), size, format.c_str(), args ...);

            return new std::string(buffer.get(), buffer.get()+size-1);

        }

    };

}
