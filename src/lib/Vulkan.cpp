/*
File: Vulkan.cpp
Author: Lars Vidar Magnusson
*/

#include <vulkan/vulkan.h>

#include "../GaME.h"
#include "Vulkan.h"

const string &Vulkan::GetErrorString(VkResult result) {
  if (result == VK_SUCCESS)
    return string("Success");
  else if (result == VK_NOT_READY)
    return string("Not Ready");
  else if (result == VK_TIMEOUT)
    return string("Timeout");
  else if (result == VK_EVENT_SET)
    return string("Event Set");
  else if (result == VK_EVENT_RESET)
    return string("Event Reset");
  else if (result == VK_INCOMPLETE)
    return string("Incomplete");
  else if (result == VK_ERROR_OUT_OF_HOST_MEMORY)
    return string("Out of Host Memory");
  else if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
    return string("Out of Device Memory");
  else if (result == VK_ERROR_INITIALIZATION_FAILED)
    return string("Initialization Failed");
  else if (result == VK_ERROR_DEVICE_LOST)
    return string("Device Lost");
  else if (result == VK_ERROR_MEMORY_MAP_FAILED)
    return string("Memory Map Failed");
  else if (result == VK_ERROR_LAYER_NOT_PRESENT)
    return string("Layer Not Present");
  else if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
    return string("Extension Not Present");
  else if (result == VK_ERROR_FEATURE_NOT_PRESENT)
    return string("Feature Not Present");
  else if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
    return string("Incompatible Driver");
  else if (result == VK_ERROR_TOO_MANY_OBJECTS)
    return string("Too Many Objects");
  else if (result == VK_ERROR_FORMAT_NOT_SUPPORTED)
    return string("Format Not Supported");
  else if (result == VK_ERROR_FRAGMENTED_POOL)
    return string("Fragmented Pool");
  else
    return string("UNKNOWN Vulkan Error");
}
