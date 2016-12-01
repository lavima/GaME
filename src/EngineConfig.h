/*
File: EngineConfig.h
Author: Lars Vidar Magnusson
*/

#ifndef __ENGINECONFIG__
#define __ENGINECONFIG__

class AddinConfig;

/**
 * Engine Configuration with XML backend. 
 */
class EngineConfig {

private:

  xercesc::DOMDocument *document;

  PlatformConfig *platformConfig;
  std::vector<AddinConfig *> addins;
  
  EngineConfig() {}
  ~EngineConfig();

public:

  static EngineConfig *Load(const char *filename);

  PlatformConfig *GetPlatformConfig();
  int GetNumAddins();
  AddinConfig *GetAddin(int index);

};

class AddinConfig {

private:

  const char *source;

  AddinConfig() {}

public:

  static AddinConfig *Load(xercesc::DOMElement *element);

  const char *GetSource();

};

#endif
