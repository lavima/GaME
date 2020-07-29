/*
File: Addin.cpp
Author: Lars Vidar Magnusson
 */

#include "../GaME.h"

namespace game::addin {

    Addin::Addin(AddinHeader* header) 
        : handle_(nullptr), header_(unique_ptr<AddinHeader>(header)), create_fun(nullptr) {}
    
    void Addin::Register(Engine& engine, AddinHeader& header) {
     
        assert(create_fun);

        AddinBindingInfo binding_info;
        create_fun(engine, header, &binding_info);

        if (binding_info.type_flags&static_cast<uint32_t>(AddinType::System)) {

            for (auto& system_info:header.GetSystemInfos()) {
                
                const string& type_name = system_info.get().GetName();

                SystemConfig::RegisterType(type_name, binding_info.system_creator);
                System::RegisterType(type_name, binding_info.system_creator);
                framework::Component::RegisterType(type_name, binding_info.system_creator);

            }

        }

    }

    Addin* Addin::Load(Engine& engine, const string& filename) {

        Addin* addin = new Addin(data::Data::Load<AddinHeader>(filename));
        AddinHeader& header = addin->GetHeader();

        string libraryFilename = lib::FilePath::GetFilename(header.GetLibraryFilename());

        addin->handle_ = engine.GetPlatform().LoadLibrary(libraryFilename);
        if (!addin->handle_) {
            delete addin;
            return nullptr;
        }

        void* address = engine.GetPlatform().LoadLibrarySymbol(addin->handle_, ADDINFUN_REGISTERADDIN);
        if (!address) {
            delete addin;
            return nullptr;
        }
        addin->create_fun = (AddinFun_CreateAddin)address;

        addin->Register(engine, header);

        return addin;

    }

    bool Addin::Unload(Engine& engine) {

        if (!handle_)
            return false;

        engine.GetPlatform().UnloadLibrary(handle_);

        return true;

    }


    AddinHeader& Addin::GetHeader() { return *(this->header_); }

    AddinType Addin::GetType() const {
        return header_->GetType();
    }
    
}