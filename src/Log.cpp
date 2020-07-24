/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

namespace game {

    Log::Log(EventType level) {

        this->level_ = level;

        out_string_ = unique_ptr<stringstream>(new stringstream());
        out_streams_.push_back(OutStream{ EventType::All, out_string_.get() });

    }

    Log::Log(const string& filename, EventType level) {

        this->level_ = level;

        out_main_ = unique_ptr<ofstream>(new ofstream(filename, ios::out));
        out_streams_.push_back(OutStream{ EventType::All, out_main_.get() });
        out_string_ = unique_ptr<stringstream>(new stringstream());
        out_streams_.push_back(OutStream{ EventType::All, out_string_.get() });

    }

    Log::Log(ostream& out, EventType level) {

        this->level_ = level;

        out_streams_.push_back(OutStream{ EventType::All, &out });
        out_string_ = unique_ptr<stringstream>(new stringstream());
        out_streams_.push_back(OutStream{ EventType::All, out_string_.get() });

    }

    Log::~Log() {

        if (out_main_)
            (*out_main_).close();

    }

    void Log::AddListener(LogListener* listener) {

        listeners_.push_back(listener);

    }

    void Log::AddOutputStream(ostream& out, EventType level) {

        out_streams_.push_back(OutStream{ level, &out });

    }

    void Log::SetLevel(EventType level) { this->level_ = level; }
    EventType Log::GetLevel() { return level_; }

    void Log::output(EventType type, const string& text) {

        for (auto os:out_streams_) {
            if (os.level<type)
                continue;
            *os.out<<text;
        }

    }

    void Log::dispatchEvent(EventType type, const string& text) {

        for (auto listener:listeners_) {
            if (listener->GetLevel()<type)
                continue;
            listener->Event(type, text);
        }

    }

}