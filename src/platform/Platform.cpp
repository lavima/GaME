/*
File: Platform.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

// 
// Declare the static member pointer. The creation of the object uses a First Use idiom 
// to avoid static fiasco.
//
unordered_map<string, Platform::Creator*>* Platform::implementations_ = nullptr;


Platform *Platform::Create(Engine &engine, PlatformConfig &config) {

    if (!implementations_->count(config.GetImplementationName()))
        return nullptr;

    Platform::Creator* creator = 
        (Platform::Creator*)implementations_->at(config.GetImplementationName());
    
    return creator->Create(engine, config);

}

const unordered_map<KeyCode, reference_wrapper<const InputKey>> Platform::GetInputKeys() {
    return unordered_map<KeyCode, reference_wrapper<const InputKey>>(input_keys_.begin(), input_keys_.end()); 
}

void Platform::RegisterImplementation(const string &name, Platform::Creator* creator) {

    if (!implementations_)
        implementations_ = new unordered_map<string, Platform::Creator*>();

    implementations_->insert_or_assign(name, creator);

}

Engine &Platform::GetEngine() { return engine_; }
PlatformConfig& Platform::GetConfig() { return config_; }
unordered_map<KeyCode, InputKeyWritable> Platform::GetWritableInputKeys() { return input_keys_; }
