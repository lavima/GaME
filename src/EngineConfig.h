/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

/**
 * Engine Configuration with XML backend.
 */
class EngineConfig {

private:

    string filename;
    string logFilename;

    vector<string> addinFilenames;

    pugi::xml_document *xmlDocument;

    EngineConfig() {}

public:

    EngineConfig(const string &filename, const string &logFilename);
    EngineConfig(const string &filename, const string &logFilename, const vector<string> &addinFilenames);
    EngineConfig(const string &filename);
    EngineConfig(pugi::xml_document &xmlDocument);
    ~EngineConfig();

    void AddAddinFilename(const string &addinFilename);

    const string &GetFilename();
    const string &GetLogFilename();
    const vector<string> &GetAddinFilenames();

};
