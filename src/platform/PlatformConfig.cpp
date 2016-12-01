/* 
File: PlatformConfig.cpp
Author: Lars Vidar Magnusson
*/

#include "PlatformConfig.h"

PlatformConfig::PlatformConfig(bool handlesInput) { this->handlesInput = handlesInput; }

bool PlatformConfig::GetHandlesInput() { return handlesInput; }
