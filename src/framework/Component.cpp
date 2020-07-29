#include "../GaME.h"

namespace game::framework {


    unordered_map<string, Component::ICreator*>* Component::creators_ = nullptr;

    void Component::RegisterType(const string& type_name, Component::ICreator *creator) {
        
        if (!creators_)
            creators_ = new unordered_map<string, ICreator*>();

        creators_->insert_or_assign(type_name, creator);

    }

    Component* Component::Create(const string& name, const string& type_name) {

        assert(creators_);

        if (creators_->find(type_name) == creators_->end())
            return nullptr;

        return (*creators_)[type_name]->Create(name, type_name);

    }

    Component* Component::Create(ComponentConfig& config) {

        assert(creators_);

        if (creators_->find(config.GetTypeName())==creators_->end())
            return nullptr;

        return (*creators_)[config.GetTypeName()]->Create(config);

    }

}