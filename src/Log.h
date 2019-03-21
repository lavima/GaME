/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

enum EventType {
    EVENT_ERROR = 1,
    EVENT_WARNING = 2,
    EVENT_DEBUG = 3
};

#define ERROR_PREFIX "ERROR: "
#define WARNING_PREFIX "WARNING: "
#define INFO_PREFIX "INFO: "

class LogListener;

/*
* This class contains functionality for logging events.
*/
class Log {

private:

    ostream *out;

    list<LogListener *> listeners;

    int listenLevel;

public:

    Log();
    Log(const string &filename);

    template<typename ... T> void AddEvent(const string &format, T ... args);
    template<typename ... T> void AddEvent(EventType eventType, const string &format, T ... args);

    void AddListener(LogListener *listener);

    void SetLevel(int level);
    int GetLevel();

};

class LogListener {

public:

    virtual void NewEvent(const string &text) = 0;

};
