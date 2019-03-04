/*
File: InfoBase.h
Author: Lars Vidar Magnusson
*/

#pragma once

class _InfoBase {

private:


protected:

    string name;
    string description;
    Version version;

    _InfoBase(const string &name, const string &description, const Version &version);
    _InfoBase(const string &&name, const string &&description, const Version &&version);
    _InfoBase(pugi::xml_node &xmlNode);
    _InfoBase(pugi::xml_node &&xmlNode);

    _InfoBase() {}
    ~_InfoBase();

public:

    const string &GetName() const;
    const string &GetDescription() const;
    const Version &GetVersion() const;

};

