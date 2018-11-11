/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum EventType {
    EVENT_ERROR,
    EVENT_WARNING,
    EVENT_INFO
};

#define ERROR_PREFIX "ERROR: "
#define WARNING_PREFIX "WARNING: "
#define INFO_PREFIX "INFO: "

class LogListener;

typedef std::vector<LogListener *> LogListenerVector;
typedef LogListenerVector::iterator LogListenerVectorIter;

class Log {

private:

    LogListenerVector listeners;

    int level;

public:

    Log();
    Log(const std:string &filename);

    void AddEvent(EventType addinType, const std::string &format, ...);

    void AddListener(int typeFlag, LogListener *listener);

    void SetLevel(int level);
    int GetLevel();

};

class LogListener {

public:

    virtual void NewEvent(const std::string &text) = 0;

};
