/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define DEFAULT_ENGINE_CONFIG "default.engine_config"
#define DEFAULT_ENGINE_LOG "engine.log"

class DefaultEngineConfig : public EngineConfig {
public:

    DefaultEngineConfig() 
        : EngineConfig(DEFAULT_ENGINE_CONFIG, DEFAULT_ENGINE_LOG) {}

};
