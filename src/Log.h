/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Event type_ enumeration
*/
enum class EventType {
    Error = 0, 
    Warning = 1,
    Info = 2, 
    Debug = 3,
    All = 4
};

#define ERROR_PREFIX string("ERROR: ") 
#define WARNING_PREFIX string("WARNING: ")
#define INFO_PREFIX string("INFO: ")
#define DEBUG_PREFIX string("DEBUG: ")

class LogListener;

/*
* A log_ with different event levels. Events are filtered in accordance with the log_ instance 
* iisten level.
*
* Supports event listeners_ through the LogListener interface. Event listeners_ can have different 
* listen level than the log_ itself.
* Supports multiple output streams. Note that the Log class does not close the streams 
* before destruction, except in the cases where the stream has been created internally. Output 
* streams can have different listen levels than the log_ itself.
*/
class Log {

private:

    unique_ptr<ofstream> out_main_;
    unique_ptr<stringstream> out_string_;

    struct OutStream {
        EventType level;
        ostream *out;
    };

    vector<OutStream> out_streams_;

    list<LogListener *> listeners_;

    EventType level_;

public:

    Log(EventType level = EventType::All);
    Log(const string &filename, EventType level = EventType::All);
    Log(ostream &out, EventType level = EventType::All);

    ~Log();

    template<typename ... T> void AddEvent(const string &format, T ... args) {

        unique_ptr<string> eventText(StringUtil::Create(format, args ...)); 
        (*eventText).append("\n");
        output(EventType::All, *eventText);
        dispatchEvent(EventType::All, *eventText);

    }

    template<typename ... T> void AddEvent(EventType type, const string &format, T ... args) {

        if (type > level_)
            return;

        unique_ptr<string> eventText(StringUtil::Create(format, args ...)); 
        (*eventText).append("\n");
        if (type == EventType::Error)
            output(EventType::Error, ERROR_PREFIX + *eventText);
        else if (type ==EventType::Warning)
            output(EventType::Warning, WARNING_PREFIX + *eventText);
        else if (type ==EventType::Info)
            output(EventType::Info, INFO_PREFIX + *eventText);
        else if (type==EventType::Debug)
            output(EventType::Debug, DEBUG_PREFIX+*eventText);
        else // Info | All
            output(EventType::All, *eventText);

        dispatchEvent(type, *eventText);

    }

    void AddListener(LogListener *listener);
    void AddOutputStream(ostream &out, EventType level = EventType::All);

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
