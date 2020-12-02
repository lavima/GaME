/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

    /*
    * Event type enumeration
    */
    enum class GAME_API EventType {
        Error = 0,
        Warning = 1,
        Info = 2,
        Debug = 3,
        Trace = 4
    };

#define ERROR_PREFIX std::string("ERROR: ") 
#define WARNING_PREFIX std::string("WARNING: ")
#define INFO_PREFIX std::string("INFO: ")
#define DEBUG_PREFIX std::string("DEBUG: ")
#define TRACE_PREFIX std::string("TRACE: ")

    class LogListener;

    /*
    * A log with different event levels. Events are filtered in accordance with the log instance
    * iisten level.
    *
    * Supports event listeners through the LogListener interface. Event listeners can have different
    * listen level than the log itself.
    * Supports multiple output streams. Note that the Log class does not close the streams
    * before destruction, except in the cases where the stream has been created internally. Output
    * streams can have different listen levels than the log itself.
    */
    class GAME_API Log {

    private:

        static Log *singleton_;

        std::unique_ptr<std::ofstream> out_main_;

        std::vector<std::ostream*> out_streams_;

        std::list<LogListener*> listeners_;

        Log(const std::string& filename);
        Log(std::ostream& out);

        ~Log();


    public:

        static Log& Get();
        static void Set(Log& singleton);
        
        template<typename ... T> void Add(const std::string& filename, int line_number, const std::string& format, T ... args) {

            std::unique_ptr<std::string> eventText(lib::StringUtil::Format(format, args ...));
            (*eventText).append("\n");
            output(EventType::Trace, *eventText);
            dispatchEvent(EventType::Trace, *eventText);

        }

        template<typename ... T> void Add(const std::string& filename, int line_number, EventType type, const std::string& format, T ... args) {

            std::unique_ptr<std::string> eventText(lib::StringUtil::Format(format, args ...));
            (*eventText).append("\n");
            auto file_line_prefix = std::unique_ptr<std::string>(lib::StringUtil::Format("[%s %d] ", filename.c_str(), line_number));
            if (type==EventType::Error)
                output(EventType::Error, *file_line_prefix+ERROR_PREFIX+*eventText);
            else if (type==EventType::Warning)
                output(EventType::Warning, *file_line_prefix+WARNING_PREFIX+*eventText);
            else if (type==EventType::Info)
                output(EventType::Info, *file_line_prefix+INFO_PREFIX+*eventText);
            else if (type==EventType::Debug)
                output(EventType::Debug, *file_line_prefix+DEBUG_PREFIX+*eventText);
            else // Trace
                output(EventType::Trace, *file_line_prefix+TRACE_PREFIX+*eventText);

            dispatchEvent(type, *eventText);

        }

        void AddListener(LogListener* listener);
        void AddOutputStream(std::ostream& out);

    private:

        void output(EventType type, const std::string& text);
        void dispatchEvent(EventType type, const std::string& text);

    };

    class GAME_API LogListener {
    public:
        virtual void Event(EventType type, const std::string& text) = 0;
    };

#define LOG_ERROR(message, ...) Log::Get().Add(__FILE__, __LINE__, EventType::Error, message, __VA_ARGS__)
#define LOG_WARNING(message, ...) Log::Get().Add(__FILE__, __LINE__, EventType::Warning, message, __VA_ARGS__)
#define LOG_INFO(message, ...) Log::Get().Add(__FILE__, __LINE__, EventType::Info, message, __VA_ARGS__)
#define LOG_DEBUG(message, ...) Log::Get().Add(__FILE__, __LINE__, EventType::Debug, message, __VA_ARGS__)
#define LOG_TRACE(message, ...) Log::Get().Add(__FILE__, __LINE__, EventType::Trace, message, __VA_ARGS__)

}