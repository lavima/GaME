/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game {
    class Engine;
}

namespace game::addin {

    class ISystemProvider;
    class IComponentProvider;

    struct AddinBindingInfo {
        
        uint32_t type_flags;

        ISystemProvider* system_provider;

        IComponentProvider* component_provider;

    };

    typedef bool (*AddinFun_Register)(Engine&, AddinHeader&, AddinBindingInfo* info);

#define ADDINFUN_REGISTERADDIN "Register"

    /*
    * Addin provides functionality for loading external functionality into the engine
    */
    class GAME_API Addin {
    private:

        void* handle_;

        std::unique_ptr<AddinHeader> header_;

        AddinFun_Register register_fun;

        Addin(AddinHeader* header);

        void Register(Engine& engine, AddinHeader& header);

    public:

        static Addin* Load(Engine& engine, const std::string& filename);

        bool Unload(Engine& engine);

        AddinHeader& GetHeader();

        AddinType GetType() const;

    };

}