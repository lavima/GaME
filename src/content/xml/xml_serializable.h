/*
File: IXmlSerializable.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::content::xml {

    /*
    * IXmlSerializable is a interface implemented by objects that can be serialized 
    * to and from XML
    */
    class GAME_API IXmlSerializable {

    public:

        virtual bool Load(XmlNode root_node) = 0;
        virtual bool Save(XmlNode root_node) = 0;

    };

}
