/*
File: XmlData.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define EXTENSION_XML "xml"

/*
* Base class for XML serializable classes.
*/
class XmlData : public WritableData, public XmlSerializable {
private:

    XmlDocument xml_document_;

public:

    XmlData(const string &filename);
    XmlData(const string &filename, XmlDocument document);

    bool Load() override;
    virtual bool Load(XmlNode) = 0;

    bool Save() override;
    virtual bool Save(XmlNode) = 0;


protected:

     XmlDocument GetDocument();

private:

    //class Loader : public DataLoader {
    //private:

    //    static Loader singleton_;

    //    Loader();

    //public:
    //    
    //    Data *Load(const string &filename_); 

    //};
};
