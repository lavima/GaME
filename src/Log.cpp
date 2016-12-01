/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <vector>

#include "Log.h"

Log *Log::singleton = NULL;

Log *Log::GetSingleton() {

  if (singleton == NULL)
    singleton = new Log();  
  
  return singleton;

}

void Log::AddEvent(EventType type, const char *format, ...) {

  if (type > level)
    return;

  va_list args;

  char *formatBuffer = NULL;
  if (type == ERROR) {
    formatBuffer = (char *)malloc(strlen(ERROR_PREFIX) + strlen(format));
    strcpy(formatBuffer, ERROR_PREFIX);
    strcat(formatBuffer, format);
  }
  else if (type == WARNING) {
    formatBuffer = (char *)malloc(strlen(WARNING_PREFIX) + strlen(format));
    strcpy(formatBuffer, WARNING_PREFIX);
    strcat(formatBuffer, format);
  }
  else if (type == INFO) {
    formatBuffer = (char *)malloc(strlen(INFO_PREFIX) + strlen(format));
    strcpy(formatBuffer, INFO_PREFIX);
    strcat(formatBuffer, format);
  }

  const char *finalFormat = NULL;
  if (type == COMMAND)
    finalFormat = format;
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
