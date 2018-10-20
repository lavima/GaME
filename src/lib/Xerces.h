/*
File: Xerces.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XERCESTRANSCODE(STRING) xercesc::XMLString::transcode(STRING)

class Xerces {
public:
    static xercesc::DOMDocument *ParseDocument(const std::string &filename);
    static const std::string &GetElementText(xercesc::DOMElement *element);
};