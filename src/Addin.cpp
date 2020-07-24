/*
File: Addin.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

namespace game {

    Addin::Addin(AddinHeader* header) 
        : handle_(nullptr), header_(unique_ptr<AddinHeader>(header)), register_fun_(nullptr) {}
    
    void Addin::Register(Engine& engine, AddinHeader& header) {
     
        assert(register_fun_);
        register_fun_(engine, header);

    }

    void Addin::Unregister(Engine& engine) {
    
        assert(unregister_fun_);
        unregister_fun_(engine);

    }

    Addin* Addin::Load(Engine& engine, const string& filename) {

        Addin* newAddin = new Addin(data::Data::Load<AddinHeader>(filename));
        AddinHeader& header = newAddin->GetHeader();

        string libraryFilename = lib::FilePath::GetFilename(header.GetLibraryFilename());

        newAddin->handle_ = engine.GetPlatform().LoadLibrary(libraryFilename);
        if (!newAddin->handle_) {
            delete newAddin;
            return nullptr;
        }

        void* address = engine.GetPlatform().LoadLibrarySymbol(newAddin->handle_, ADDINFUN_REGISTERADDIN);
        if (!address) {
            delete newAddin;
            return nullptr;
        }
        newAddin->register_fun_ = (RegisterAddinFun)address;

        address = engine.GetPlatform().LoadLibrarySymbol(newAddin->handle_, ADDINFUN_UNREGISTERADDIN);
        if (!address) {
            delete newAddin;
            return nullptr;
        }
        newAddin->unregister_fun_ = (UnregisterAddinFun)address;
       

        newAddin->Register(engine, header);

        //if (header.GetType()==AddinType::EngineComponent) {

        //    auto createAddr = engine.GetPlatform().LoadLibrarySymbol(newAddin->handle_, ADDINFUN_ENGINECOMPONENT_CREATE);
        //    if (!createAddr) {
        //        delete newAddin;
        //        return nullptr;
        //    }
        //    newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENT_CREATE] = createAddr;

        //    auto loadConfigAddr = engine.GetPlatform().LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_LOAD);
        //    if (!loadConfigAddr) {
        //        delete newAddin;
        //        return nullptr;
        //    }
        //    newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENTCONFIG_LOAD] = loadConfigAddr;

        //    auto saveConfigAddr = engine.GetPlatform().LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_SAVE);
        //    if (!saveConfigAddr) {
        //        delete newAddin;
        //        return nullptr;
        //    }
        //    newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENTCONFIG_SAVE] = saveConfigAddr;

        //    for (const SystemVersionInfo& componentInfo:header.GetEngineComponents()) {

        //        const string& name = componentInfo.GetName();
        //        System::RegisterProvider(name, (CreateEngineComponentFun)createAddr);
        //        SystemConfig::RegisterProvider(name, (LoadEngineComponentConfigFun)loadConfigAddr, (SaveEngineComponentConfigFun)saveConfigAddr);

        //    }
        //}

        return newAddin;

    }

    bool Addin::Unload(Engine& engine) {

        if (!handle_)
            return false;

        Unregister(engine);

        engine.GetPlatform().UnloadLibrary(handle_);

        return true;

    }

    

    AddinHeader& Addin::GetHeader() { return *(this->header_); }

    AddinType Addin::GetType() const {
        return header_->GetType();
    }
}