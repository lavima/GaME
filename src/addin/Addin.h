/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::addin {

    class ISystemProvider;

    struct AddinBindingInfo {
        
        uint32_t type_flags;

        ISystemProvider* system_creator;

    };

    typedef bool (*AddinFun_CreateAddin)(Engine&, AddinHeader&, AddinBindingInfo* info);

#define ADDINFUN_REGISTERADDIN "RegisterAddin"

    /*
    * Addin provides functionality for loading external functionality into the engine
    */
    class GAME_API Addin {
    private:

        void* handle_;

        unique_ptr<AddinHeader> header_;

        AddinFun_CreateAddin create_fun;

        Addin(AddinHeader* header);

        void Register(Engine& engine, AddinHeader& header);

    public:

        static Addin* Load(Engine& engine, const string& filename);

        bool Unload(Engine& engine);

        AddinHeader& GetHeader();

        AddinType GetType() const;

    };

}