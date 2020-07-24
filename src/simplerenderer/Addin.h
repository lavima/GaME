/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

    extern "C" {

        __declspec(dllexport) void RegisterAddin(Engine& engine, AddinHeader& header);

        __declspec(dllexport) void UnregisterAddin(Engine& engine);

    }

}
