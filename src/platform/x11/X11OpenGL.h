/*
File: X11SystemOpenGL.h
Author: Lars Vidar Magnusson
*/

#ifndef __SYSTEM_X11_X11SYSTEMOPENGL__
#define __SYSTEM_X11_X11SYSTEMOPENGL__

#define KEY_EVENT_MASK (KeyPressMask | KeyReleaseMask)
#define MOUSE_EVENT_MASK (ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask )
#define X_EVENT_MASK (KEY_EVENT_MASK | MOUSE_EVENT_MASK | VisibilityChangeMask | StructureNotifyMask )


class X11SystemOpenGL : public System {

private:

  /*
  * Private structure for holding X related data
  */
  struct X11ClientData {

    Display *display;
    int screen;
    Window window;
    GLXContext context;
    XSetWindowAttributes windowAttributes;
    int majorVersion, minorVersion;
    int glxMajorVersion, glxMinorVersion;
    XF86VidModeModeInfo originalModeInfo;
    Atom wmDeleteMessage;

  };


  X11PlatformConfig *config;

  X11ClientData clientData;

public:

  PlatformConfig *LoadPlatformConfig(xercesc::DOMElement *element);

  /**
  * Xlib implementation of System::Initialize
  */
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
