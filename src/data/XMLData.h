/*
File: XmlData.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::data {

#define EXTENSION_XML "xml"

    /*
    * Base class for XML serializable classes.
    */
    class GAME_API XmlData : public WritableData, public xml::IXmlSerializable {
    private:

        xml::XmlDocument xml_document_;

    public:

        XmlData(const string& filename);
        XmlData(const string& filename, xml::XmlDocument document);

        bool Load() override;
        virtual bool Load(xml::XmlNode) = 0;

        bool Save() override;
        virtual bool Save(xml::XmlNode) = 0;

        void Unload() override;


    protected:

        xml::XmlDocument GetDocument();

    private:

        //class Loader : public DataLoader {
        //private:

        //    static Loader singleton_;

        //    Loader();

        //public:
        //    
        //    Data *Create(const string &filename_); 

        //};
    };

}