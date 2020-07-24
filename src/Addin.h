/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {

    class Engine;

    typedef void (*RegisterAddinFun)(Engine&, AddinHeader&);
    typedef void (*UnregisterAddinFun)(Engine&);

#define ADDINFUN_REGISTERADDIN "RegisterAddin"
#define ADDINFUN_UNREGISTERADDIN "UnregisterAddin"

    /*
    * Addin provides functionality for loading external functionality into the engine
    */
    class GAME_API Addin {
    private:

        void* handle_;

        unique_ptr<AddinHeader> header_;

        RegisterAddinFun register_fun_;
        UnregisterAddinFun unregister_fun_;

        Addin(AddinHeader* header);

        void Register(Engine& engine, AddinHeader& header);
        void Unregister(Engine& engine);

    public:

        static Addin* Load(Engine& engine, const string& filename);

        bool Unload(Engine& engine);

        AddinHeader& GetHeader();

        AddinType GetType() const;

    };

}