/*
File: X11Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#ifdef OS_XLIB

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <v8.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <xercesc/dom/DOM.hpp>

#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>

#include <vector>
#include <unordered_map>

#include "../../lib/CStringHash.h"
#include "../PlatformConfig.h"
#include "../Platform.h"
#include "../../scripting/ScriptContext.h"
#include "../../scripting/Script.h"
#include "../../framework/GameTime.h"
#include "../../framework/Game.h"
#include "../../AddinInfo.h"
#include "../../AddinContainer.h"
#include "../../Addin.h"
#include "../../EngineConfig.h"
#include "../../EngineComponent.h"
#include "../../Engine.h"
#include "X11Config.h"
#include "X11Vulkan.h"

Platform *Platform::singleton = nullptr;

Platform *Platform::GetSingleton() {

  if (singleton == nullptr)
    singleton = new X11Vulkan();  
  
  return singleton;

}

PlatformConfig *X11Vulkan::LoadConfig(xercesc::DOMElement *element) {

  return X11Config::Load(element);

}

bool X11Vulkan::Initialize(PlatformConfig *config) {
  
  this->config = (X11Config *)config;

  if (!XInitThreads()) {
    printf("XInitThreads failed\n");
    return false;
  }
  
  if (!(x11.display = XOpenDisplay(nullptr))) {
    printf("Could not connect to the X server\n");
    return false; 
  }

  XF86VidModeQueryVersion(x11.display, &x11.majorVersion, &x11.minorVersion);
  printf("X11 %d.%d Initialized.\n", x11.majorVersion, x11.minorVersion);

  x11.screen = DefaultScreen(x11.display);

  Window rootWindow = RootWindow(x11.display, x11.screen);

  XF86VidModeModeInfo **modes;
  int numModes, bestMode, index;
  XF86VidModeGetAllModeLines(x11.display, x11.screen, &numModes, &modes);
  x11.originalModeInfo = *modes[0];
  if (this->config->GetFullscreen()) {
    bestMode = -1;
    for (index = 0; index < numModes; index++) {
      if (modes[index]->hdisplay != this->config->GetWidth() || modes[index]->vdisplay != this->config->GetHeight())
        continue;

      bestMode = index;
    }

    if (bestMode == -1) {
      printf("Could not find a suitable fullscreen video mode (%d x %d).\n", 
        this->config->GetWidth(), this->config->GetHeight());
      this->config->SetFullscreen(false);
    }
  }

  Visual *visual = DefaultVisual(x11.display, x11.screen);
  int depth = DefaultDepth(x11.display, x11.screen);

  x11.windowAttributes.background_pixel = BlackPixel(x11.display, x11.screen);
  x11.windowAttributes.colormap = XCreateColormap(x11.display, rootWindow, visual, AllocNone);
  x11.windowAttributes.border_pixel = 0;
  x11.windowAttributes.event_mask = X_EVENT_MASK; 

  unsigned long mask;
  if (this->config->GetFullscreen()) {
  
    XF86VidModeSwitchToMode(x11.display, x11.screen, modes[bestMode]);
    XF86VidModeSetViewPort(x11.display, x11.screen, 0, 0);
        
    x11.windowAttributes.override_redirect = True;

    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect;

  }
  else 
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  x11.window = 
    XCreateWindow(x11.display, rootWindow, 0, 0, 
      this->config->GetWidth(), this->config->GetHeight(), 
      0, depth, InputOutput, visual, 
      mask, &x11.windowAttributes);  

  XStoreName(x11.display, x11.window, "GaME");

  if (this->config->GetFullscreen()) {

    XWarpPointer(x11.display, None, x11.window, 0, 0, 0, 0, 0, 0);
    XGrabKeyboard(x11.display, x11.window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(x11.display, x11.window, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, 
            x11.window, None, CurrentTime);

  }
  else {

    x11.wmDeleteMessage = XInternAtom(x11.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(x11.display, x11.window, &x11.wmDeleteMessage, 1);

  }

  XMapWindow(x11.display, x11.window);

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
  extensions[1] = strdup("VK_KHR_xlib_surface");
  createInfo.enabledExtensionCount = 2;
  createInfo.ppEnabledExtensionNames = extensions;

  createInfo.enabledLayerCount = 0;

  if (vkCreateInstance(&createInfo, nullptr, &(x11.vk.instance)) != VK_SUCCESS) {
    printf("could not create Vulkan instance.\n");
    return false;
  }

  PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR = 
    (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(x11.vk.instance, "vkCreateXlibSurfaceKHR");
  if (!vkCreateXlibSurfaceKHR) {
    printf("could not load PFN_vkCreateXlibSurfaceKHR.\n");
    return false;
  }

  VkXlibSurfaceCreateInfoKHR sci;
  memset(&sci, 0, sizeof(sci));
  sci.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
  sci.dpy = x11.display;
  sci.window = x11.window;
  
  if (vkCreateXlibSurfaceKHR(x11.vk.instance, &sci, nullptr, &(x11.vk.surface)) != VK_SUCCESS) {
    printf("vkCreateXlibSurfaceKHR failed.\n");
    return false;
  }

  XFree(visual);
  XFree(modes);

  return true;

}

void X11Vulkan::Shutdown() {
  
  assert(config);

  if (config->GetFullscreen()) {
    XF86VidModeSwitchToMode(x11.display, x11.screen, &x11.originalModeInfo);
    XF86VidModeSetViewPort(x11.display, x11.screen, 0, 0);
  }

  XDestroyWindow(x11.display, x11.window);

  XCloseDisplay(x11.display);

  config = nullptr;

}

void X11Vulkan::HandleEvents() {

  XEvent event;
  while (XPending(x11.display) > 0) {
    
    XNextEvent(x11.display, &event);
    if (event.type == ClientMessage && event.xclient.data.l[0] == x11.wmDeleteMessage)
      ENGINE->Stop();

  }

}

void X11Vulkan::SwapBuffers() {
}

void *X11Vulkan::LoadLibrary(const char *filename) {

  void *handle = dlopen(filename, RTLD_LAZY);
  if (!handle)
    printf("Could not load the dynamic library: %s\n", filename);

  return handle;

}

void X11Vulkan::UnloadLibrary(void *handle) {

  if (dlclose(handle))
    printf("Could not unload the dynamic library\n");

}

void *X11Vulkan::LoadLibrarySymbol(void *handle, const char *name) {

    void *symbolHandle = dlsym(handle, name);

    char *error = dlerror();
    if (error != nullptr) {
      printf("Could not load the symbol %s from the dynamic library\n", name);
      return nullptr;
    }

    return symbolHandle;

}

unsigned long long X11Vulkan::GetSystemTime() {

  unsigned long low, high;

  __asm__ __volatile__(
    "xor %%eax,%%eax\n" \
    "cpuid\n" 
    ::: "%rax", "%rbx", "%rcx", "%rdx");

  __asm__ __volatile__(
    "rdtsc\n" \
    : "=a" (low), "=d" (high));
  
  return (unsigned long long)high << 32 | low;

}

#endif // OS_XLIB

