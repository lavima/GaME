/*
File: StringUtil.h
Author: Lars Vidar Magnusson
*/

#pragma once

class StringUtil {
public:

    template <typename ... T> inline static string *Create(const string &format, T ... args) {

        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        unique_ptr<char[]> buffer(new char[size]);
        snprintf(buffer.get(), size, format.c_str(), args ...);
        
        return new string(buffer.get(), buffer.get() + size - 1);

    }

};
