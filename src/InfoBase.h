/*
File: InfoBase.h
Author: Lars Vidar Magnusson
 */

#pragma once

class InfoBase {

private:

    const string *name;
    const string *description;
    const string *version;

    InfoBase() {}

protected:

    template<typename T> static T *Load(T *info, pugi::xml_node &xmlElement);

public:

    const string &GetName();
    const string &GetDescription();
    const string &GetVersion();

};
