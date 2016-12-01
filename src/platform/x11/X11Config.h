/* 
File: X11Config.h
Author: Lars Vidar Magnusson
*/

#ifndef __PLATFORM_X11_X11CONFIG__
#define __PLATFORM_X11_X11CONFIG__

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FULLSCREEN false

class X11Config : public PlatformConfig {

private:

  int width;
  int height;
  bool fullscreen;

  X11Config() : PlatformConfig(true) {}

public:

  static X11Config *Load(xercesc::DOMElement *element);

  int GetWidth();
  int GetHeight();
  bool GetFullscreen();
  void SetFullscreen(bool fullscreen);

};

#endif
