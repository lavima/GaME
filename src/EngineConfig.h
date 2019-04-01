/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define ENGINE_CONFIG_EXTENSION "engine_config"

/**
 * Engine Configuration with XML backend.
 */
class EngineConfig : XMLData<EngineConfig> {

private:

    unique_ptr<string> logFilename;

    vector<string> addinFilenames;
    vector<reference_wrapper<const string>> addinFilenamesConst;

public:

    EngineConfig(const string &filename);
    EngineConfig(const string &filename, const string &logFilename);
    ~EngineConfig();

    static EngineConfig *Load(const string &filename);

    bool HasLogFilename(); 
    const string &GetLogFilename();
    void SetLogFilename(const string &logFilename);

    void AddAddinFilename(const string &addinFilename);
    const vector<reference_wrapper<const string>> GetAddinFilenames();

    virtual bool Load();
    virtual bool Save();

private:

    class EngineConfigFactory : DataFactory<EngineConfig> {
    private:

        static EngineConfigFactory singleton;

        EngineConfigFactory();

    public:

        EngineConfig *Load(const string &filename);

    };

};
