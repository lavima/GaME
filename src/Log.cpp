/*
File: Log.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

Log::Log() {

    out = new stringstream();

}

Log::Log(const string &filename) {

    ofstream *outFile = new ofstream();
    (*outFile).open(filename, ios::out);

    out = outFile;

}

template<typename ... T> void Log::AddEvent(EventType addinType, const string &format, T && ... args) {

    if (addinType > listenLevel)
        return;

    if (addinType == EVENT_ERROR) 
        (*out) << ERROR_PREFIX << StringUtil::Format(format, args ...); 
    else if (addinType == EVENT_WARNING) 
        (*out) << WARNING_PREFIX << StringUtil::Format(format, args ...); 
    else if (addinType == EVENT_DEBUG)
        (*out) << INFO_PREFIX << StringUtil::Format(format, args ...); 

}

void Log::AddListener(LogListener *listener) {

    listeners.push_back(listener);

}

void Log::SetLevel(int level) { this->listenLevel = level; }
int Log::GetLevel() { return listenLevel; }
