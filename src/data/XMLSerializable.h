/*
File: XMLSerializable.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* An interface for objects that can be serialized to and from XML 
*/
class XMLSerializable {

public:

    virtual bool Load(pugi::xml_node rootNode) = 0;
    virtual bool Save(pugi::xml_node rootNode) = 0;

};
