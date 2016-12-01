/*
File: X11Vulkan.h
Author: Lars Vidar Magnusson
*/

#ifndef __PLATFORM_X11_X11SYSTEMVULKAN__
#define __PLATFORM_X11_X11SYSTEMVULKAN__

#define KEY_EVENT_MASK (KeyPressMask | KeyReleaseMask)
#define MOUSE_EVENT_MASK (ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask )
#define X_EVENT_MASK (KEY_EVENT_MASK | MOUSE_EVENT_MASK | VisibilityChangeMask | StructureNotifyMask )


class X11Vulkan : public Platform {

private:

  struct VulkanData {

    VkInstance instance;
    VkSurfaceKHR surface;

  };

  struct X11Data {

    Display *display;
    int screen;
    Window window;

    XSetWindowAttributes windowAttributes;

    int majorVersion, minorVersion;

    XF86VidModeModeInfo originalModeInfo;

    Atom wmDeleteMessage;

    VulkanData vk;

  };


  X11Config *config;

  X11Data x11;

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

#endif
