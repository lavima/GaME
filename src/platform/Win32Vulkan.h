/*
File: X11Vulkan.h
Author: Lars Vidar Magnusson
*/

#ifdef OS_WIN

#pragma once

using namespace std;

#define TYPENAME_WIN32VULKAN "Win32Vulkan"

class Win32Vulkan : public Platform {

private:

    Win32Vulkan(PlatformConfig &config);

	struct VulkanData {

		VkInstance Instance;
		VkSurfaceKHR Surface;

	};

	struct Win32Data {

		HWND		Window;
		HINSTANCE	Instance;

		VulkanData Vk;

	};

    GraphicalPlatformConfig *config;

	Win32Data win32;

    string commandLine;

public:

    static Platform * Load(PlatformConfig &config);

    bool Initialize(PlatformConfig &config);

	void Shutdown();

	void HandleEvents();

	void SwapBuffers();

#ifdef LoadLibrary
#undef LoadLibrary
#endif
	void *LoadLibrary(const string &filename);

	void UnloadLibrary(void *handle);

	void *LoadLibrarySymbol(void *handle, const string &name);

	unsigned long long GetSystemTime();

#ifdef GetCommandLine
#undef GetCommandLine
#endif
    const string &GetCommandLine();

private:

    class __Register {
    private:
        static __Register singleton;
    public:
        __Register() { Platform::RegisterImplementation(TYPENAME_WIN32VULKAN, &(Win32Vulkan::Load)); }
    };

    
};

#endif // OS_WIN32