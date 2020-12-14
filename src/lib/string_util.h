/*
File: string_util.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::lib {

    class GAME_API StringUtil final {

    private:
        static void argsToStrings(std::vector<std::string> &arg_strings) {}

        template <typename T, typename ... R> 
        static void argsToStrings(std::vector<std::string> &arg_strings, T arg, R ... args) {
            std::stringstream arg_string;
            arg_string << arg;
            arg_strings.push_back(arg_string.str());
            argsToStrings(arg_strings, args...);
        }

    public:

        template <typename ... T> static std::string* Format(const std::string& format, T ... args) {

            std::vector<std::string> arg_strings; 
            StringUtil::argsToStrings(arg_strings, args...);

            size_t args_total_length = 0;
            for (const std::string& arg_string : arg_strings) {
                args_total_length += arg_string.length();
            }

            // Find the length of the final string
            size_t total_length = 0;
            for (size_t i=0; i<format.length(); ++i) {
                
                if (format[i] != '%') {
                    ++total_length;
                    continue;
                }

                if (format[i+1] == '%') {
                    ++total_length;
                    ++i;
                    continue;
                }

                size_t j = i++;
                while (std::isdigit(format[++j]));                
                size_t arg_index = std::stoi(format.substr(i, j-i));
                total_length += arg_strings[arg_index].length();
                i = j-1;

            }
            
            // Build the final string

            std::string* final = new std::string();
            final->reserve(total_length);

            for (size_t i=0; i<format.length(); ++i) {

                if (format[i] != '%') {
                    final->push_back(format[i]);
                    continue;
                }

                if (format[i+1] == '%') {
                    ++i;
                    final->push_back(format[i]);
                    continue;
                }

                size_t j = i++;
                while (std::isdigit(format[++j])); 
                size_t arg_index = std::stoi(format.substr(i, j-i));
                const std::string& arg = arg_strings[arg_index];
                final->append(arg);
                i = j-1;

            }

            return final;

        }

    };

}
