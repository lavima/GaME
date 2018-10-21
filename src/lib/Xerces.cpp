/*
File: XercesUtils.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace xercesc;

xercesc::DOMDocument *Xerces::ParseDocument(const string &filename) {

  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    return NULL;
  }

  XercesDOMParser* parser = new XercesDOMParser();
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  ErrorHandler* errorHandler = (ErrorHandler*) new HandlerBase();
  parser->setErrorHandler(errorHandler);

  try {
    parser->parse(filename.c_str());
  }
  catch (const XMLException& toCatch) {
    return NULL;
  }
  catch (const DOMException& toCatch) {
    return NULL;
  }

  xercesc::DOMDocument *document = parser->adoptDocument();

  delete parser;
  delete errorHandler;

  return document;

}

const string *Xerces::GetElementText(DOMElement *element) {

    DOMNode *textNode = element->getFirstChild();
    if (textNode->getNodeType() != DOMNode::TEXT_NODE)
        return nullptr;

    DOMText *text = (DOMText *)textNode;
    char *cText = XERCESTRANSCODE(text->getTextContent());
    string *ret = new string(cText);
    XMLString::release(&cText);
    
    return ret;

}
