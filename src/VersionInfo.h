/*
File: VersionInfo.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define XMLNAME_INFOBASE_NAME "Name"
#define XMLNAME_INFOBASE_DESCRIPTION "Description"
#define XMLNAME_INFOBASE_VERSION XMLNAME_VERSION 

/*
* VersionInfo contains information that is used to specify type information.
*/
class VersionInfo : public XmlSerializable {
private:

    string name_;
    string description_;
    Version version_;

protected:

    VersionInfo() {}
    VersionInfo(const string& name, const Version& version);
    VersionInfo(const string &name, const string &description, const Version &version);
    VersionInfo(const string &&name, const string &&description, const Version &&version);
    VersionInfo(XmlNode xml_node);

    static bool Load(VersionInfo *info, XmlNode root_node);
    static bool Save(VersionInfo &info, XmlNode root_node);

    void SetName(const string &name);
    void SetDescription(const string &description);
    void SetVersion(const Version &version);

public: 

    bool Load(XmlNode root_node) override;
    bool Save(XmlNode root_node) override;

    const string &GetName() const;
    const string &GetDescription() const;
    const Version &GetVersion() const;

};
