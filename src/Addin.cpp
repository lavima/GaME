/*
File: Addin.cpp
Author: Lars Vidar Magnusson
 */

#include "GaME.h"

Addin *Addin::Load(Platform &platform, const string &filename) {

    Addin *newAddin = new Addin();

    newAddin->info = unique_ptr<AddinInfo>(Data::Load<AddinInfo>(filename));
    AddinInfo &info = newAddin->GetInfo();

    string libraryFilename = FilePath::GetFilename(info.GetLibraryFilename());

    newAddin->handle = platform.LoadLibrary(libraryFilename);
    if (!newAddin->GetHandle()) {
        delete newAddin;
        return nullptr;
    }

    void *address = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_REGISTERADDIN);
    if (!address) {
        delete newAddin;
        return nullptr;
    }

    newAddin->symbolMap[ADDINFUN_REGISTERADDIN] = address;

    RegisterAddinFun registerAddin = (RegisterAddinFun)address;
    registerAddin(info);

    if (info.GetType() == ENGINE_COMPONENT_ADDIN) {

        createAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENT_CREATE);
        if (!createAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbolMap[ADDINFUN_ENGINECOMPONENT_CREATE] = createAddr;

        loadConfigAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_LOAD);
        if (!loadConfigAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbolMap[ADDINFUN_ENGINECOMPONENTCONFIG_LOAD] = loadConfigAddr;

        saveConfigAddr = platform.LoadLibrarySymbol(newAddin->GetHandle(), ADDINFUN_ENGINECOMPONENTCONFIG_SAVE);
        if (!saveConfigAddr) {
            delete newAddin;
            return nullptr;
        }
        newAddin->symbolMap[ADDINFUN_ENGINECOMPONENTCONFIG_SAVE] = saveConfigAddr;

        for (const EngineComponentInfo &componentInfo : info.GetEngineComponents()) {

            const string &name = componentInfo.GetName();
            EngineComponent::RegisterProvider(name, (CreateEngineComponentFun)createAddr);
            EngineComponentConfig::RegisterProvider(name, (LoadEngineComponentConfigFun)loadConfigAddr, (SaveEngineComponentConfigFun)saveConfigAddr);

        }

    }

    return newAddin;

}

bool Addin::HasSymbol(const string &name) { 
    return this->symbolMap.find(name) != this->symbolMap.end(); 
}

void *Addin::GetSymbolAddr(const string &name) {

    if (this->HasSymbol(name))
        return this->symbolMap[name];

    return nullptr;

}

const vector<reference_wrapper<const string>> Addin::GetLoadedSymbolNames() const {

    vector<reference_wrapper<const string>> symbolNames;

    for (pair<string, void *> symbolPair : symbolMap)
        symbolNames.push_back(symbolPair.first);

    return symbolNames;

}

AddinInfo &Addin::GetInfo() { return *(this->info); }
void *Addin::GetHandle() { return this->handle; }

