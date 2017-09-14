/*
File: Xerces.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XERCESTRANSCODE(STRING) xercesc::XMLString::transcode(STRING)

xercesc::DOMDocument *XercesParseDocument(const std::string &filename);