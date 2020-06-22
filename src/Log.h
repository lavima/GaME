/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Event type enumeration
*/
enum EventType {
    EVENT_ERROR = 0, 
    EVENT_WARNING = 1,
    EVENT_INFO = 2, 
    EVENT_DEBUG = 3,
    EVENT_ALL = 4
};

#define ERROR_PREFIX string("ERROR: ") 
#define WARNING_PREFIX string("WARNING: ")
#define INFO_PREFIX string("INFO: ")
#define DEBUG_PREFIX string("DEBUG: ")

class LogListener;

/*
* A log with different event levels. Events are filtered in accordance with the log instance 
* iisten level.
*
* Supports event listeners through the LogListener interface. Event listeners can have different 
* listen level than the log itself.
* Supports multiple output streams. Note that the Log class does not close the streams 
* before destruction, except in the case where the stream has been created internally. Output 
* streams can have different listen levels than the log itself.
*/
class Log {

private:

    unique_ptr<ofstream> fileOut;
    unique_ptr<stringstream> textOut;

    struct outStream {
        EventType Level;
        ostream *Out;
    };

    vector<outStream> outStreams;

    list<LogListener *> listeners;

    EventType listenLevel;

public:

    Log(EventType level = EVENT_ALL);
    Log(const string &filename, EventType level = EVENT_ALL);
    Log(ostream &out, EventType level = EVENT_ALL);

    ~Log();

    template<typename ... T> void AddEvent(const string &format, T ... args) {

        unique_ptr<string> eventText(StringUtil::Create(format, args ...)); 
        (*eventText).append("\n");
        output(EVENT_ALL, *eventText);
        dispatchEvent(EVENT_ALL, *eventText);

    }

    template<typename ... T> void AddEvent(EventType type, const string &format, T ... args) {

        if (type > listenLevel)
            return;

        unique_ptr<string> eventText(StringUtil::Create(format, args ...)); 
        (*eventText).append("\n");
        if (type == EVENT_ERROR) 
            output(EVENT_ERROR, ERROR_PREFIX + *eventText);
        else if (type == EVENT_WARNING) 
            output(EVENT_WARNING, WARNING_PREFIX + *eventText);
        else if (type == EVENT_DEBUG)
            output(EVENT_DEBUG, DEBUG_PREFIX + *eventText);
        else // EVENT_INFO | EVENT_ALL
            output(EVENT_ALL, *eventText);

        dispatchEvent(type, *eventText);

    }

    void AddListener(LogListener *listener);
    void AddOutputStream(ostream &out, EventType level = EVENT_ALL);

    void SetLevel(EventType level);
    EventType GetLevel();

private:

    void output(EventType type, const string &text);
    void dispatchEvent(EventType type, const string &text);

};

class LogListener {

public:

    virtual void Event(EventType type, const string &text) = 0;
    virtual EventType GetLevel() = 0;

};
