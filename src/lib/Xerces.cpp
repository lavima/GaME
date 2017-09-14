/*
File: XercesUtils.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

xercesc::DOMDocument *XercesParseDocument(const string &filename) {

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
    parser->parse(filename.c_str());
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
