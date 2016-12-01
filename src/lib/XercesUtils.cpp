/*
File: XercesUtils.cpp
Author: Lars Vidar Magnusson
*/

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include "XercesUtils.h"

xercesc::DOMDocument *XercesParseDocument(const char *filename) {

  try {
    xercesc::XMLPlatformUtils::Initialize();
  }
  catch (const xercesc::XMLException& toCatch) {
    return NULL;
  }

  xercesc::XercesDOMParser* parser = new xercesc::XercesDOMParser();
  parser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
  xercesc::ErrorHandler* errorHandler = (xercesc::ErrorHandler*) new xercesc::HandlerBase();
  parser->setErrorHandler(errorHandler);

  try {
    parser->parse(filename);
  }
  catch (const xercesc::XMLException& toCatch) {
    return NULL;
  }
  catch (const xercesc::DOMException& toCatch) {
    return NULL;
  }

  xercesc::DOMDocument *document = parser->adoptDocument();

  delete parser;
  delete errorHandler;

  return document;

}
