/*
File: X11SystemOpenGL.cpp
Author: Lars Vidar Magnusson
*/

#ifdef OS_XLIB

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <v8.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "../../library/CStringHash.h"
#include "../PlatformConfig.h"
#include "../System.h"
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
#include "X11PlatformConfig.h"
#include "X11SystemOpenGL.h"

System *System::singleton = NULL;

System *System::GetSingleton() {

  if (singleton == NULL)
    singleton = new X11SystemOpenGL();  
  
  return singleton;

}

PlatformConfig *X11SystemOpenGL::LoadPlatformConfig(xercesc::DOMElement *element) {

  return X11PlatformConfig::Load(element);

}

bool X11SystemOpenGL::Initialize(PlatformConfig *config) {
  
  this->config = (X11PlatformConfig *)config;

  if (!XInitThreads()) {
    printf("XInitThreads failed\n");
    return false;
  }
  
  if (!(clientData.display = XOpenDisplay(NULL))) {
    printf("Could not connect to the X server\n");
    return false; 
  }

  XF86VidModeQueryVersion(clientData.display, &clientData.majorVersion, &clientData.minorVersion);
  printf("X11 %d.%d Initialized.\n", clientData.majorVersion, clientData.minorVersion);

  clientData.screen = DefaultScreen(clientData.display);

  Window rootWindow = RootWindow(clientData.display, clientData.screen);

  XF86VidModeModeInfo **modes;
  int numModes, bestMode, index;
  XF86VidModeGetAllModeLines(clientData.display, clientData.screen, &numModes, &modes);
  clientData.originalModeInfo = *modes[0];
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
  
  int glAttributes[] = {
    GLX_RGBA,
    GLX_DOUBLEBUFFER,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
		None
	};

  XVisualInfo *visualInfo = glXChooseVisual(clientData.display, clientData.screen, glAttributes);
  if (!visualInfo) {
    printf("Could not find a suitable visual\n");
    return false;
  }
  
  glXQueryVersion(clientData.display, &clientData.glxMajorVersion, &clientData.glxMinorVersion);
  printf("GLX %d.%d Initialized.\n", clientData.glxMajorVersion, clientData.glxMinorVersion);

  clientData.context = glXCreateContext(clientData.display, visualInfo, 0, GL_TRUE);

  clientData.windowAttributes.background_pixel = BlackPixel(clientData.display, clientData.screen);
  clientData.windowAttributes.colormap = 
    XCreateColormap(clientData.display, rootWindow, visualInfo->visual, AllocNone);
  clientData.windowAttributes.border_pixel = 0;
  clientData.windowAttributes.event_mask = X_EVENT_MASK; 

  unsigned long mask;
  if (this->config->GetFullscreen()) {
  
    XF86VidModeSwitchToMode(clientData.display, clientData.screen, modes[bestMode]);
    XF86VidModeSetViewPort(clientData.display, clientData.screen, 0, 0);
        
    clientData.windowAttributes.override_redirect = True;

    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect;

  }
  else 
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  clientData.window = 
    XCreateWindow(clientData.display, rootWindow, 0, 0, 
      this->config->GetWidth(), this->config->GetHeight(), 
      0, visualInfo->depth, InputOutput, visualInfo->visual, 
      mask, &clientData.windowAttributes);  

  XStoreName(clientData.display, clientData.window, "GaME");

  if (this->config->GetFullscreen()) {

    XWarpPointer(clientData.display, None, clientData.window, 0, 0, 0, 0, 0, 0);
    XGrabKeyboard(clientData.display, clientData.window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(clientData.display, clientData.window, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, 
            clientData.window, None, CurrentTime);

  }
  else {

    clientData.wmDeleteMessage = XInternAtom(clientData.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(clientData.display, clientData.window, &clientData.wmDeleteMessage, 1);

  }

  XMapWindow(clientData.display, clientData.window);

  glXMakeCurrent(clientData.display, clientData.window, clientData.context);

  if (!glXIsDirect(clientData.display, clientData.context)) {
    printf("Direct rendering is not possible.\n");
    return false;
  }

  printf("GL_RENDERER %s\n", glGetString(GL_RENDERER));
  printf("GL_EXTENSIONS %s\n", glGetString(GL_EXTENSIONS));

  XFree(visualInfo);
  XFree(modes);

  return true;

}

void X11SystemOpenGL::Shutdown() {
  
  assert(config);

  if (clientData.context)
  {
    if (!glXMakeCurrent(clientData.display, None, NULL))
      printf("Could not release drawing context.\n");

    glXDestroyContext(clientData.display, clientData.context);
    clientData.context = NULL;
  }

  if (config->GetFullscreen()) {
    XF86VidModeSwitchToMode(clientData.display, clientData.screen, &clientData.originalModeInfo);
    XF86VidModeSetViewPort(clientData.display, clientData.screen, 0, 0);
  }

  XDestroyWindow(clientData.display, clientData.window);

  XCloseDisplay(clientData.display);

  config = NULL;

}

void X11SystemOpenGL::HandleEvents() {

  XEvent event;
  while (XPending(clientData.display) > 0) {
    
    XNextEvent(clientData.display, &event);
    if (event.type == ClientMessage && event.xclient.data.l[0] == clientData.wmDeleteMessage)
      ENGINE->Stop();

  }

}

void X11SystemOpenGL::SwapBuffers() {
  glXSwapBuffers(clientData.display, clientData.window);
}

void *X11SystemOpenGL::LoadLibrary(const string &filename) {

  void *handle = dlopen(filename, RTLD_LAZY);
  if (!handle)
    printf("Could not load the dynamic library: %s\n", filename);

  return handle;

}

void X11SystemOpenGL::UnloadLibrary(void *handle) {

  if (dlclose(handle))
    printf("Could not unload the dynamic library\n");

}

void *X11SystemOpenGL::LoadLibrarySymbol(void *handle, const string &name) {

    void *symbolHandle = dlsym(handle, name);

    char *error = dlerror();
    if (error != NULL) {
      printf("Could not load the symbol %s from the dynamic library\n", name);
      return NULL;
    }

    return symbolHandle;

}

unsigned long long X11SystemOpenGL::GetSystemTime() {

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
