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

#define ADDINFUN_REGISTER_TEMPLATE bool(Engine&, AddinHeader&, AddinBindingInfo*)
    typedef std::function<ADDINFUN_REGISTER_TEMPLATE> AddinFun_Register;

#define ADDINFUN_REGISTERADDIN "Register"

    /*
    * Addin provides functionality for loading external functionality into the engine
    */
    class GAME_API Addin {
    private:

        platform::LibraryHandle handle_;

        std::unique_ptr<AddinHeader> header_;

        AddinFun_Register register_fun_;

        Addin(AddinHeader* header);

        void Register(Engine& engine, AddinHeader& header);

    public:

        ~Addin();

        static Addin* Load(Engine& engine, const std::string& filename);

        bool Unload(Engine& engine);

        AddinHeader& GetHeader();

        AddinType GetType() const;

    };

}
