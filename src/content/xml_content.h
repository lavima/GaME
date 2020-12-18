/*
File: XmlContent.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::content {

#define EXTENSION_XML ".xml"

    /*
    * Base class for XML serializable classes.
    */
    class GAME_API XmlContent : public WritableContent, public xml::IXmlSerializable {
    private:

        xml::XmlDocument xml_document_;

    public:

        XmlContent(const std::string& filename);
        XmlContent(const std::string& filename, xml::XmlDocument document);

        bool Load() override;
        bool Load(xml::XmlNode) override = 0;

        bool Save() override;
        bool Save(xml::XmlNode) override = 0;

        void Unload() override;


    protected:

        xml::XmlDocument GetDocument();

    private:

        //class ICreator : public ILoader {
        //private:

        //    static ICreator singleton_;

        //    ICreator();

        //public:
        //    
        //    Data *Load(const string &filename_); 

        //};
    };

}
