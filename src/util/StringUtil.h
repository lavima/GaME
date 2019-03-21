/*
File: StringUtil.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

class StringUtil {
public:

    template <typename ... T> static string *Format(const string &format, T ... args);

};
