/*
File: Win32Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#ifdef OS_WIN32

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <windows.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include <vector>
#include <unordered_map>

#include "../../lib/CommonTypes.h"
#include "../../lib/CStringHash.h"
#include "../../lib/Vulkan.h"
#include "../PlatformConfig.h"
#include "../Platform.h"
#include "../../scripting/ScriptEnvironment.h"
#include "../../scripting/Script.h"
#include "../../framework/GameTime.h"
#include "../../framework/Game.h"
#include "../../AddinInfo.h"
#include "../../AddinContainer.h"
#include "../../Addin.h"
#include "../../EngineConfig.h"
#include "../../EngineComponent.h"
#include "../../Engine.h"
#include "Win32Config.h"
#include "Win32Vulkan.h"

Platform *Platform::singleton = nullptr;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Platform *Platform::GetSingleton() {

	if (singleton == nullptr)
		singleton = new Win32Vulkan();

	return singleton;

}

PlatformConfig *Win32Vulkan::LoadConfig(xercesc::DOMElement *element) {

	return Win32Config::Load(element);

}

bool Win32Vulkan::Initialize(PlatformConfig *config) {

	this->config = (Win32Config *)config;

	RECT		windowRect;				
	windowRect.left = 0;			
	windowRect.right = this->config->GetWidth();
	windowRect.top = 0;
	windowRect.bottom = this->config->GetHeight();

	win32.Instance = GetModuleHandle(NULL);

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = win32.Instance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GaME";

	if (!RegisterClass(&wc)) {
		return FALSE;	
	}

	if (this->config->GetFullscreen()) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = this->config->GetWidth();
		dmScreenSettings.dmPelsHeight = this->config->GetHeight();
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			return FALSE;
		}
	}

	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	DWORD extendedStyle = WS_EX_APPWINDOW;
	if (this->config->GetFullscreen()) {
		style |= WS_POPUP;
    extendedStyle |= WS_EX_TOPMOST;
		ShowCursor(FALSE);
	}
	else {
		style |= WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, style, FALSE, extendedStyle);

  win32.Window = 
    CreateWindowEx(extendedStyle, 
      L"GaME", L"GaME", 
      style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
      0, 0,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      NULL,
      NULL,
      win32.Instance,
      NULL);
	if (!win32.Window) {
		return FALSE;
	}

  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "GaME";
  appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  char **extensions = (char **)calloc(2, sizeof(char*));
  extensions[0] = strdup("VK_KHR_surface");
  extensions[1] = strdup("VK_KHR_win32_surface");
  createInfo.enabledExtensionCount = 2;
  createInfo.ppEnabledExtensionNames = extensions;

  createInfo.enabledLayerCount = 0;

  VkResult result;
  result = vkCreateInstance(&createInfo, nullptr, &(win32.Vk.Instance));
  if (result != VK_SUCCESS) {
    printf("Could not create Vulkan instance: %s\n", Vulkan::GetErrorString(result));
    return false;
  }

  PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
  vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(win32.Vk.Instance, "vkCreateWin32SurfaceKHR");
  if (!vkCreateWin32SurfaceKHR) {
    printf("Vulkan instance does not implement the VK_KHR_win32_surface extension.\n");
    return false;
  }

  VkWin32SurfaceCreateInfoKHR sci;
  memset(&sci, 0, sizeof(sci));
  sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  sci.hinstance = win32.Instance;
  sci.hwnd = win32.Window;

  result = vkCreateWin32SurfaceKHR(win32.Vk.Instance, &sci, nullptr, &(win32.Vk.Surface));
  if (result != VK_SUCCESS) {
    printf("Win32: Failed to create Vulkan surface: %s", Vulkan::GetErrorString(result));
  }

	ShowWindow(win32.Window, SW_SHOW);
	SetForegroundWindow(win32.Window);
	SetFocus(win32.Window);

	return true;
}

void Win32Vulkan::Shutdown() {
}

void Win32Vulkan::HandleEvents() {
}

void Win32Vulkan::SwapBuffers() {
}

void * Win32Vulkan::LoadLibrary(const char * filename) {
  return nullptr;
}

void Win32Vulkan::UnloadLibrary(void * handle) {
}

void * Win32Vulkan::LoadLibrarySymbol(void * handle, const char * name) {
  return nullptr;
}

unsigned long long Win32Vulkan::GetSystemTime() {
  return 0;
}

#endif // OS_WIN32