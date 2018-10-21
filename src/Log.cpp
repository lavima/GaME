/*
File: Log.cpp
Author: Lars Vidar Magnusson
*/

#include <stdarg.h>

#include "GaME.h"


void Log::AddEvent(EventType addinType, const string &format, ...) {

  if (addinType > level)
    return;

  va_list args;

  char *formatBuffer = NULL;
  if (addinType == EVENT_ERROR) {
    formatBuffer = (char *)malloc(strlen(ERROR_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, ERROR_PREFIX);
    strcat(formatBuffer, format.c_str());
  }
  else if (addinType == EVENT_WARNING) {
    formatBuffer = (char *)malloc(strlen(WARNING_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, WARNING_PREFIX);
    strcat(formatBuffer, format.c_str());
  }
  else if (addinType == EVENT_INFO) {
    formatBuffer = (char *)malloc(strlen(INFO_PREFIX) + strlen(format.c_str()));
    strcpy(formatBuffer, INFO_PREFIX);
    strcat(formatBuffer, format.c_str());
  }

  const char *finalFormat = NULL;
  if (addinType == EVENT_COMMAND)
    finalFormat = format.c_str();
  else
    finalFormat = formatBuffer;
  

  size_t textSize = strlen(finalFormat) * 3;
  char *text = (char *)malloc(textSize);

  va_start(args, finalFormat);
  
  vprintf(finalFormat, args);

  vsnprintf(text, textSize, finalFormat, args);
  if (addinType == EVENT_ERROR)
    for (LogListenerVectorIter iter=errorListeners.begin(); iter!=errorListeners.end(); ++iter)
      (*iter)->NewEvent(text);

  va_end(args);

}

void Log::AddListener(int typeFlag, LogListener *listener) {

  if (typeFlag & EVENT_COMMAND) 
    commandListeners.push_back(listener);
  if (typeFlag & EVENT_ERROR) 
    errorListeners.push_back(listener);
  if (typeFlag & EVENT_WARNING) 
    warningListeners.push_back(listener);
  if (typeFlag & EVENT_INFO) 
    infoListeners.push_back(listener);

}

void Log::SetLevel(int level) { this->level = level; }
int Log::GetLevel() { return level; }
