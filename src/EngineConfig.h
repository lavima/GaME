/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define EXTENSION_ENGINECONFIG "engine_config"

#define XMLNAME_ENGINECONFIG "EngineConfig"
#define XMLNAME_ENGINECONFIG_LOGFILENAME "LogFilename"
#define XMLNAME_ENGINECONFIG_ADDIN XMLNAME_ADDIN

/**
 * Engine Configuration with XML backend.
 */
class EngineConfig : public XMLData {

private:

    unique_ptr<string> logFilename;

    vector<string> addinFilenames;

public:

    EngineConfig(const string &filename);
    EngineConfig(const string &filename, const string &logFilename);

    bool HasLogFilename(); 
    const string &GetLogFilename();
    void SetLogFilename(const string &logFilename);

    void AddAddinFilename(const string &addinFilename);
    const vector<reference_wrapper<const string>> GetAddinFilenames();

    using XMLData::Load;
    bool Load(pugi::xml_node rootNode);
    using XMLData::Save;
    bool Save(pugi::xml_node rootNode);

private:

    class __Factory : public DataFactory {
    private:

        static __Factory singleton;

        __Factory();

    public:

        Data *Load(const string &filename);

    };

};
