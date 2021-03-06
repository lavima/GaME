/*
File: X11Vulkan.h
Author: Lars Vidar Magnusson
*/

#ifdef OS_WIN

#pragma once

#define WIN32VULKAN_NAME "Win32Vulkan"

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

public:

    static Platform * Create(PlatformConfig &config);

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

private:

    class __Register {
    private:
        static __Register singleton;
    public:
        __Register() { Platform::RegisterImplementation(WIN32VULKAN_NAME, &(Win32Vulkan::Create)); }
    };

    
};

#endif // OS_WIN32
