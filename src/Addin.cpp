/*
File: Addin.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

Addin *Addin::Load(Platform &platform, const string &filename) {

    Addin *newAddin = new Addin(Data::Load<AddinHeader>(filename));
    AddinHeader &header = newAddin->GetHeader();

    string libraryFilename = FilePath::GetFilename(header.GetLibraryFilename());

    newAddin->handle_ = platform.LoadLibrary(libraryFilename);
    if (!newAddin->GetHandle()) {
        delete newAddin;
        return nullptr;
    }

    void *address = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_REGISTERADDIN);
    if (!address) {
        delete newAddin;
        return nullptr;
    }

    newAddin->symbol_map_[ADDINFUN_REGISTERADDIN] = address;

    RegisterAddinFun registerAddin = (RegisterAddinFun)address;
    registerAddin(header);

    if (header.GetType() == AddinType::EngineComponent) {

        auto createAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENT_CREATE);
        if (!createAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENT_CREATE] = createAddr;

        auto loadConfigAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_LOAD);
        if (!loadConfigAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENTCONFIG_LOAD] = loadConfigAddr;

        auto saveConfigAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_SAVE);
        if (!saveConfigAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbol_map_[ADDINFUN_ENGINECOMPONENTCONFIG_SAVE] = saveConfigAddr;

        for (const EngineComponentVersionInfo &componentInfo : header.GetEngineComponents()) {

            const string& name = componentInfo.GetName();
            EngineComponent::RegisterProvider(name, (CreateEngineComponentFun)createAddr);
            EngineComponentConfig::RegisterProvider(name, (LoadEngineComponentConfigFun)loadConfigAddr, (SaveEngineComponentConfigFun)saveConfigAddr);

        }
    }

    return newAddin;

}

bool Addin::HasSymbol(const string &name) { 
    return this->symbol_map_.find(name) != this->symbol_map_.end(); 
}

void *Addin::GetSymbolAddr(const string &name) {

    if (this->HasSymbol(name))
        return this->symbol_map_[name];

    return nullptr;

}

const vector<reference_wrapper<const string>> Addin::GetLoadedSymbolNames() const {

    vector<reference_wrapper<const string>> symbolNames;

    for (pair<string, void *> symbolPair : symbol_map_)
        symbolNames.push_back(symbolPair.first);

    return symbolNames;

}

AddinHeader &Addin::GetHeader() { return *(this->header_); }
void *Addin::GetHandle() { return this->handle_; }

AddinType Addin::GetType() const {
    return header_->GetType();
}

