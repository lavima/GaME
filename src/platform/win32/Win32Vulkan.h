/*
File: X11Vulkan.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

class Win32Vulkan : public Platform {

private:

	struct VulkanData {

		VkInstance Instance;
		VkSurfaceKHR Surface;

	};

	struct Win32Data {

		HWND		Window;
		HINSTANCE	Instance;

		VulkanData Vk;

	};

	Win32Config *config;

	Win32Data win32;

public:

	PlatformConfig *LoadConfig(xercesc::DOMElement *element);

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

};

