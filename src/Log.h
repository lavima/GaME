/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#ifndef __LOG__
#define __LOG__

enum EventType {
  COMMAND = 1,
  ERROR = 2,
  WARNING = 4,
  INFO = 8
};

#define ERROR_PREFIX "ERROR: "
#define WARNING_PREFIX "WARNING: "
#define INFO_PREFIX "INFO: "

class LogListener;

typedef std::vector<LogListener *> LogListenerVector;
typedef LogListenerVector::iterator LogListenerVectorIter;

#define LOG Log::GetSingleton()

class Log {

private:

  static Log *singleton;

  LogListenerVector commandListeners;
  LogListenerVector errorListeners;
  LogListenerVector warningListeners;
  LogListenerVector infoListeners;

  int level;

  Log() {}

public:

  static Log *GetSingleton();

  void AddEvent(EventType type, const char *format, ...);

  void AddListener(int typeFlag, LogListener *listener);

  void SetLevel(int level);
  int GetLevel();

};

class LogListener {

public:
  
  virtual void NewEvent(const char *text) = 0;

};

#endif
