/*
File: XercesUtils.h
Author: Lars Vidar Magnusson
*/

#ifndef __XERCESUTILS__
#define __XERCESUTILS__

#define XERCESTRANSCODE(STRING) xercesc::XMLString::transcode(STRING)

xercesc::DOMDocument *XercesParseDocument(const char *filename);

#endif
