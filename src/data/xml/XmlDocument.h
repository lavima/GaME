#pragma once

class XmlDocument {

private:

    unique_ptr<pugi::xml_document> internal_;

public:

    XmlDocument();
    XmlDocument(XmlDocument& other);

    bool Load(const string& filename);
    bool Save(const string& filename);
    
    XmlNode GetDocumentElement();

};