/*
File: Platform.h
Author: Lars Vidar Magnusson
*/

#ifndef __PLATFORM_PLATFORM__
#define __PLATFORM_PLATFORM__

#define PLATFORM Platform::GetSingleton()

/*
* Abstract base class for all platform implementations. 
*/
class Platform {

protected:

  // This has to be defined by the system implementation
  static Platform *singleton;

public:

  /*
  * Return a pointer to the singleton instance of the system. This has to defined by the system implementation
  */
  static Platform *GetSingleton();

  /*
  * Load the platform configuration from the specified XML element. This method is invoked by EngineConfig::Load() to 
  * allow each platform implementation platform specific configuration.
  */
  virtual PlatformConfig *LoadConfig(xercesc::DOMElement *element) = 0;

  virtual bool Initialize(PlatformConfig *config) = 0;

  virtual void Shutdown() = 0;

  virtual void HandleEvents() = 0;

  virtual void SwapBuffers() = 0;

  virtual void *LoadLibrary(const char *filename) = 0;

  virtual void UnloadLibrary(void *handle) = 0;

  virtual void *LoadLibrarySymbol(void *handle, const char *name) = 0;

  virtual unsigned long long GetSystemTime() = 0;

};

#endif
