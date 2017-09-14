/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include <stdarg.h>

#include "GaME.h"


Log *Log::singleton = NULL;

inline Log &Log::GetSingleton() { return *(GetSingletonPtr()); }

Log *Log::GetSingletonPtr() {

  if (singleton == NULL)
    singleton = new Log();  
  
  return singleton;

}

void Log::AddEvent(EventType type, const string &format, ...) {

  if (type > level)
    return;

  va_list args;

  char *formatBuffer = NULL;
  if (type == ERROR) {
    formatBuffer = (char *)malloc(strlen(ERROR_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, ERROR_PREFIX);
    strcat(formatBuffer, format.c_str());
  }
  else if (type == WARNING) {
    formatBuffer = (char *)malloc(strlen(WARNING_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, WARNING_PREFIX);
    strcat(formatBuffer, format.c_str());
  }
  else if (type == INFO) {
    formatBuffer = (char *)malloc(strlen(INFO_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, INFO_PREFIX);
    strcat(formatBuffer, format.c_str());
  }

  const char *finalFormat = NULL;
  if (type == COMMAND)
    finalFormat = format.c_str();
  else
    finalFormat = formatBuffer;
  

  size_t textSize = strlen(finalFormat) * 3;
  char *text = (char *)malloc(textSize);

  va_start(args, finalFormat);
  
  vprintf(finalFormat, args);

  vsnprintf(text, textSize, finalFormat, args);
  if (type == ERROR)
    for (LogListenerVectorIter iter=errorListeners.begin(); iter!=errorListeners.end(); ++iter)
      (*iter)->NewEvent(text);

  va_end(args);

}

void Log::AddListener(int typeFlag, LogListener *listener) {

  if (typeFlag & COMMAND) 
    commandListeners.push_back(listener);
  if (typeFlag & ERROR) 
    errorListeners.push_back(listener);
  if (typeFlag & WARNING) 
    warningListeners.push_back(listener);
  if (typeFlag & INFO) 
    infoListeners.push_back(listener);

}

void Log::SetLevel(int level) { this->level = level; }
int Log::GetLevel() { return level; }
