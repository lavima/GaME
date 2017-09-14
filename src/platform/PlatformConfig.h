/* 
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

class PlatformConfig {

private:

  // TODO Is this really needed? If so, come up with a better name
  bool handlesInput;

protected:

  PlatformConfig(bool handlesInput);

public:

  bool GetHandlesInput();

};