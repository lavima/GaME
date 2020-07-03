/*
File: XmlSerializable.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* An interface for objects that can be serialized to and from XML 
*/
class XmlSerializable {

public:

    virtual bool Load(XmlNode root_node) = 0;
    virtual bool Save(XmlNode root_node) = 0;

};
