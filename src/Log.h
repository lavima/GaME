/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum EventType {
    EVENT_COMMAND = 1,
    EVENT_ERROR = 2,
    EVENT_WARNING = 4,
    EVENT_INFO = 8
};

#define ERROR_PREFIX "ERROR: "
#define WARNING_PREFIX "WARNING: "
#define INFO_PREFIX "INFO: "

class LogListener;

typedef std::vector<LogListener *> LogListenerVector;
typedef LogListenerVector::iterator LogListenerVectorIter;

class Log {

private:

    LogListenerVector commandListeners;
    LogListenerVector errorListeners;
    LogListenerVector warningListeners;
    LogListenerVector infoListeners;

    int level;

public:

    Log() {}

    void AddEvent(EventType addinType, const std::string &format, ...);

    void AddListener(int typeFlag, LogListener *listener);

    void SetLevel(int level);
    int GetLevel();

};

class LogListener {

public:

    virtual void NewEvent(const std::string &text) = 0;

};