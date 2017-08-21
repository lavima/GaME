/*
File: Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "Vulkan.h"

const char *Vulkan::GetErrorString(VkResult result) {
  if (result == VK_SUCCESS)
    return "Success";
  else if (result == VK_NOT_READY)
    return "Not Ready";
  else if (result == VK_TIMEOUT)
    return "Timeout";
  else if (result == VK_EVENT_SET)
    return "Event Set";
  else if (result == VK_EVENT_RESET)
    return "Event Reset";
  else if (result == VK_INCOMPLETE)
    return "Incomplete";
  else if (result == VK_ERROR_OUT_OF_HOST_MEMORY)
    return "Out of Host Memory";
  else if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
    return "Out of Device Memory";
  else if (result == VK_ERROR_INITIALIZATION_FAILED)
    return "Initialization Failed";
  else if (result == VK_ERROR_DEVICE_LOST)
    return "Device Lost";
  else if (result == VK_ERROR_MEMORY_MAP_FAILED)
    return "Memory Map Failed";
  else if (result == VK_ERROR_LAYER_NOT_PRESENT)
    return "Layer Not Present";
  else if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
    return "Extension Not Present";
  else if (result == VK_ERROR_FEATURE_NOT_PRESENT)
    return "Feature Not Present";
  else if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
    return "Incompatible Driver";
  else if (result == VK_ERROR_TOO_MANY_OBJECTS)
    return "Too Many Objects";
  else if (result == VK_ERROR_FORMAT_NOT_SUPPORTED)
    return "Format Not Supported";
  else if (result == VK_ERROR_FRAGMENTED_POOL)
    return "Fragmented Pool";
  else
    return "UNKNOWN Vulkan Error";
}
