/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

Log::Log(EventType level) {

    this->listenLevel = level;

    textOut = unique_ptr<stringstream>(new stringstream());
    outStreams.push_back(outStream{EVENT_ALL, textOut.get()});

}

Log::Log(const string &filename, EventType level) {

    this->listenLevel = level;

    fileOut = unique_ptr<ofstream>(new ofstream(filename, ios::out));
    outStreams.push_back(outStream{EVENT_ALL, fileOut.get()});

}

Log::Log(ostream &out, EventType level) {

    this->listenLevel = level;

    outStreams.push_back(outStream{EVENT_ALL, &out});

}

Log::~Log() {

    if (fileOut)
        (*fileOut).close();

}

void Log::AddListener(LogListener *listener) {

    listeners.push_back(listener);

}

void Log::AddOutputStream(ostream &out, EventType level) {

    outStreams.push_back(outStream{level, &out});

}

void Log::SetLevel(EventType level) { this->listenLevel = level; }
EventType Log::GetLevel() { return listenLevel; }
    
void Log::output(EventType type, const string &text) {

    for (auto os : outStreams) {
        if (os.Level < type)
            continue;
        *os.Out << text;
    }

}

void Log::dispatchEvent(EventType type, const string &text) {

    for (auto listener : listeners) {
        if (listener->GetLevel() < type)
            continue;
        listener->Event(type, text);
    }

}

