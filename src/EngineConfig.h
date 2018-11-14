/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

class AddinConfig;

/**
 * Engine Configuration with XML backend.
 */
class EngineConfig {

private:

    const string *configFilename; 

    pugi::xml_document *document;

    PlatformConfig *platformConfig;
    std::vector<AddinConfig *> addins;
    const string *logFile;

    EngineConfig() {}
    ~EngineConfig();

public:

    static EngineConfig *Load(const string &filename);

    PlatformConfig &GetPlatformConfig();
    int GetNumAddins();
    AddinConfig &GetAddin(int index);

    const string &GetLogFile();

};

class AddinConfig {

private:

    const string *source;

    AddinConfig() {}

public:

    static AddinConfig *Load(pugi::xml_node &element);

    const string &GetSource();

};
