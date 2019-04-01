/*
File: XMLData.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Base class for XML serializable classes.
*/
template<typename T> class XMLData : WritableData<T> {
private:

    pugi::xml_document xmlDocument;

protected:

    XMLData(const string &filename) : WritableData<T>(filename) {}
    XMLData(const string &filename, pugi::xml_document document);

    bool LoadXML();
    bool SaveXML();

    xml_document GetXMLDocument();
    void SetXMLDocument(pugi::xml_document document);


private:

    class XMLDataFactory : DataFactory<XMLData> {
    private:

        static XMLDataFactory singleton;

        XMLDataFactory();

    public:
        
        XMLData *Load(const string &filename); 

    };
};
