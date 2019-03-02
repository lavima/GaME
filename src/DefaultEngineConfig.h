/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

class DefaultEngineConfig : public EngineConfig {
public:

    DefaultEngineConfig() : EngineConfig(string("engine.config"), string("engine.log")) {}

};
