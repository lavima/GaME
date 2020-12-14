/*
File: Platform.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::platform {

#ifdef _WINDOWS
    typedef HMODULE LibraryHandle;
#endif

    /*
    * This class provides the interface for all platform_ implementations_, and a factory function for
    * creating instance implementations_.
    */
    class GAME_API Platform {

    protected:

        /*
        * Platform::ICreator is a protected abstract class providing an interface for platform
        * implementations to be created.
        */
        class Creator {
        public:
            virtual Platform* Create(Engine& engine, PlatformConfig& config) = 0;
        };

    private:

        static std::unordered_map<std::string, Platform::Creator*>* implementations_;

        const std::string implementation_name_;

        Engine& engine_;
        PlatformConfig& config_;

        std::unordered_map<KeyCode, InputKeyWritable> input_keys_;

    protected:

        Platform(const std::string& name, Engine& engine, PlatformConfig& config);

    public:
      
        virtual ~Platform();

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

        virtual LibraryHandle LoadLibrary(const std::string& filename);

        virtual void UnloadLibrary(LibraryHandle handle);

    private:

        /*
        * TypdedFunction is a template parameter parser to determine the type of a function. This is 
        * used by LoadLibrarySymbol<T> to allow "functional template notation" in the template argument 
        * e.g. LoadLibrarySymbol<int(int)> instead of LoadLibrarySymbol<int,int> 
        *
        * TODO Why is this structure needed i.e. why can't we do this on the LoadLibrarySymbol<T> 
        * directly?
        */
        template <typename T> 
        struct TypedFunction {};

        template <typename Ret, typename... Args> 
        struct TypedFunction<Ret(Args...)> {
#ifdef _WINDOWS
            static std::function<Ret(Args...)> create(const FARPROC proc) {
                return std::function<Ret(Args...)>(reinterpret_cast<Ret (__stdcall*)(Args...)>(proc));
            }
#endif
        };  

     public:

        template<typename T> std::function<T> LoadLibrarySymbol(LibraryHandle handle, const std::string& name) {
#ifdef _WINDOWS
            FARPROC proc = GetProcAddress(handle, name.c_str());
            if (!proc)
              return nullptr;
#endif
            return TypedFunction<T>::create(proc);

        }

        virtual double GetSystemTime() = 0;

        /*
        * Creates a new map with constant reference access to all input keys
        */
        const std::unordered_map<KeyCode, std::reference_wrapper<const InputKey>> GetInputKeys();

        static Platform* Create(Engine& engine, PlatformConfig& config);

    protected:

        Engine& GetEngine();
        PlatformConfig& GetConfig();
        std::unordered_map<KeyCode, InputKeyWritable> GetWritableInputKeys();

        static void RegisterImplementation(const std::string& name, Platform::Creator* creator);

    };

}
