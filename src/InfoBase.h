/*
File: InfoBase.h
Author: Lars Vidar Magnusson
*/

#pragma once

/*
* Base class for meta information classes that can be read from XML-files
*/
class _InfoBase {

private:

    const string *name;
    const string *description;
    const Version *version;

    _InfoBase() {}

protected:

    template<typename T> static T *Load(T *info, pugi::xml_node &xmlElement);
    template<typename T> static T *Create(T *info, const string *name, const string *description, const Version *version);

public:

    ~_InfoBase();

    const string &GetName();
    const string &GetDescription();
    const Version &GetVersion();

};
