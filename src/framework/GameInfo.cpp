/*
File: GameInfo.h
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

GameInfo::~GameInfo() {
    
    delete name;
    delete description;
    delete version;

    for (EngineComponentNameIter iter = engineComponents.begin(); iter != engineComponents.end(); ++iter)
        delete (*iter).second;

}

GameInfo *GameInfo::Load(const string &filename) {
    
    xercesc::DOMDocument *document = Xerces::ParseDocument(filename);

    GameInfo *ret = new GameInfo();
    ret->filename = &filename;

    xercesc::DOMElement *rootElement = (xercesc::DOMElement *)document->getDocumentElement()->getElementsByTagName(XERCESTRANSCODE("Info"))->item(0);

    xercesc::DOMElement *nameElement = (xercesc::DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Name"))->item(0);
    ret->name = Xerces::GetElementText(nameElement);

    xercesc::DOMElement *descriptionElement = (xercesc::DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Description"))->item(0);
    ret->description = Xerces::GetElementText(descriptionElement);

    ret->version = Version::Load((xercesc::DOMElement *)rootElement->getElementsByTagName(XERCESTRANSCODE("Version"))->item(0));

    xercesc::DOMNodeList *componentNodes = document->getDocumentElement()->getElementsByTagName(XERCESTRANSCODE("EngineComponent"));
    for (int i = 0; i<componentNodes->getLength(); i++) {
        xercesc::DOMElement *componentElement = (xercesc::DOMElement *)componentNodes->item(i);
        ret->engineComponents.insert(
            EngineComponentNamePair(
                string(XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("type")))),
                new string(XERCESTRANSCODE(componentElement->getAttribute(XERCESTRANSCODE("name"))))));
    }

    return ret;
}

const string &GameInfo::GetName() const { return *name; }
const string &GameInfo::GetDescription() const { return *description; }
const Version &GameInfo::GetVersion() const { return *version; }
const EngineComponentNameMap &GameInfo::GetEngineComponents() const { return engineComponents; }