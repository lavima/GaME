/*
File: InfoBase.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_INFOBASE_NAME "Name"
#define XMLNAME_INFOBASE_DESCRIPTION "Description"
#define XMLNAME_INFOBASE_VERSION XMLNAME_VERSION 

class __InfoBase : public XMLSerializable {
private:

    string name;
    string description;
    Version version;

protected:

    __InfoBase() {}
    __InfoBase(const string &name, const string &description, const Version &version);
    __InfoBase(const string &&name, const string &&description, const Version &&version);
    __InfoBase(pugi::xml_node &xmlNode);
    __InfoBase(pugi::xml_node &&xmlNode);

    static bool Load(__InfoBase *info, pugi::xml_node &rootNode);
    static bool Save(__InfoBase &info, pugi::xml_node *rootNode);

    void SetName(const string &name);
    void SetDescription(const string &description);
    void SetVersion(const Version &version);

public: 

    bool Load(pugi::xml_node &rootNode) override; 
    bool Save(pugi::xml_node *rootNode) override;

    const string &GetName() const;
    const string &GetDescription() const;
    const Version &GetVersion() const;

};

