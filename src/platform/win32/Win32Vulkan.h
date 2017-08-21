/*
File: X11Vulkan.h
Author: Lars Vidar Magnusson
*/

#pragma once

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

	bool Initialize(PlatformConfig *config);

	void Shutdown();

	void HandleEvents();

	void SwapBuffers();

	void *LoadLibrary(const char *filename);

	void UnloadLibrary(void *handle);

	void *LoadLibrarySymbol(void *handle, const char *name);

	unsigned long long GetSystemTime();

};

