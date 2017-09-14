/*
File: Log.h
Author: Lars Vidar Magnusson
*/

#pragma once

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
#define LOG_PTR Log::GetSingletonPtr()

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

  static Log &GetSingleton();
  static Log *GetSingletonPtr();

  void AddEvent(EventType type, const std::string &format, ...);

  void AddListener(int typeFlag, LogListener *listener);

  void SetLevel(int level);
  int GetLevel();

};

class LogListener {

public:
  
  virtual void NewEvent(const std::string &text) = 0;

};