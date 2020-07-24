/*
File: Platform.h
Author: Lars Vidar Magnusson
*/

#pragma once

class game::Engine;

namespace game::platform {

    /*
    * This class provides the interface for all platform_ implementations_, and a factory function for
    * creating instance implementations_.
    */
    class GAME_API Platform {

    protected:

        /*
        * Platform::Creator is a protected abstract class providing an interface for platform
        * implementations to be created.
        */
        class Creator {
        public:
            virtual Platform* Create(Engine& engine, PlatformConfig& config) = 0;
        };

        static void RegisterImplementation(const string& name, Platform::Creator* creator);

    private:

        static unordered_map<string, Platform::Creator*>* implementations_;

        const string implementation_name_;

        Engine& engine_;
        PlatformConfig& config_;

        unordered_map<KeyCode, InputKeyWritable> input_keys_;

    protected:

        Platform(const string& name, Engine& engine, PlatformConfig& config)
            : implementation_name_(name), engine_(engine), config_(config) {}

    public:

        virtual bool Initialize() = 0;

        virtual void Shutdown() = 0;

        /*
        * Handle all input events. This should amount in an update of the input state exposed
        * by this class.
        */
        virtual void HandleEvents() = 0;

        /*
        * Swap display buffers. This is required for all platforms supporting real-time rendering
        */
        virtual void SwapBuffers() = 0;

#ifdef LoadLibrary
#undef LoadLibrary
#endif
        virtual void* LoadLibrary(const string& filename) = 0;

        virtual void UnloadLibrary(void* handle) = 0;

        virtual void* LoadLibrarySymbol(void* handle, const string& name) = 0;

        virtual double GetSystemTime() = 0;

        /*
        * Creates a new map with constant reference access to all input keys
        */
        const unordered_map<KeyCode, reference_wrapper<const InputKey>> GetInputKeys();

    public:

        static Platform* Create(Engine& engine, PlatformConfig& config);

    protected:

        Engine& GetEngine();
        PlatformConfig& GetConfig();
        unordered_map<KeyCode, InputKeyWritable> GetWritableInputKeys();

    };

}