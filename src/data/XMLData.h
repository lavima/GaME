/*
File: XMLData.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Base class for XML serializable classes.
*/
class XMLData : public WritableData, public XMLSerializable {
private:

    unique_ptr<pugi::xml_document> xmlDocument;

public:

    XMLData(const string &filename);
    XMLData(const string &filename, pugi::xml_document *document);

    bool Load();
    virtual bool Load(pugi::xml_node) = 0;

    bool Save();
    virtual bool Save(pugi::xml_node) = 0;


protected:

    static bool Parse(const string &filename, pugi::xml_document *document);

    pugi::xml_document &GetXMLDocument();

private:

    class __Factory : public DataFactory {
    private:

        static __Factory singleton;

        __Factory();

    public:
        
        Data *Load(const string &filename); 

    };
};
