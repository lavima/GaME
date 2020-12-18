/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <iostream>
#include <list>

#include "global.h"
#include "lib/format.h"
#include "Log.h"

namespace game {

    Log* Log::singleton_ = nullptr;

    Log::Log(const std::string& filename) {
        out_main_ = std::unique_ptr<std::ofstream>(new std::ofstream(filename, std::ios::out));
        out_streams_.push_back(out_main_.get());
    }

    Log::Log(std::ostream& out) {
        out_streams_.push_back(&out);
    }

    Log::~Log() {
        if (out_main_)
            (*out_main_).close();
    }

    Log& Log::Get() { 
        if (!singleton_)
            singleton_ = new Log(std::cout);
        return *singleton_;
    }

    void Log::Set(Log& singleton) { 
        singleton_ = &singleton;
    }

    void Log::AddListener(LogListener* listener) {
        listeners_.push_back(listener);
    }

    void Log::AddOutputStream(std::ostream& out) {
        out_streams_.push_back(&out);
    }

    void Log::output(EventType type, const std::string& text) {
        for (std::ostream* os:out_streams_)
            *os<<text;
    }

    void Log::dispatchEvent(EventType type, const std::string& text) {
        for (LogListener* listener:listeners_)
            listener->Event(type, text);
    }

}
