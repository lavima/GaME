/*
* Filename: GaME.h
* Author: Lars Vidar Magnusson 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <optional>
#include <unordered_map>
#include <memory>
#include <functional>
#include <algorithm>
#include <set>
#include <cassert>
#include <cstdint>

#include <windows.h>

#include <v8.h>
#include <libplatform/libplatform.h>
#ifdef PLATFORM_WIN32_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <windows.h>
#endif
#ifdef PLATFORM_GLFWVULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#endif

#include <pugixml.hpp>

using namespace std;

#include "lib/StringUtil.h"
#include "lib/FilePath.h"
#include "lib/CommandLine.h"
#include "lib/V8.h"
#include "lib/vulkan/Vulkan.h"
#include "data/DataLoader.h"
#include "data/Data.h"
#include "data/xml/XmlRange.h"
#include "data/xml/XmlAttribute.h"
#include "data/xml/XmlNode.h"
#include "data/xml/XmlDocument.h"
#include "data/xml/XmlSerializable.h"
#include "data/XmlData.h"
#include "Log.h"
#include "Version.h"
#include "VersionInfo.h"
#include "EngineComponentVersionInfo.h"
#include "AddinHeader.h"
#include "Addin.h"
#include "scripting/ScriptEnvironment.h"
#include "scripting/Scriptable.h"
#include "scripting/Script.h"

#include "platform/InputKey.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#ifdef PLATFORM_WIN32VULKAN
#include "platform/Win32Vulkan.h"
#endif
#ifdef PLATFORM_GLFWVULKAN
#include "platform/VulkanPlatform.h"
#include "platform/GLFWVulkanConfig.h"
#include "platform/GLFWVulkan.h"
#endif
#include "platform/DefaultPlatformConfig.h"
#include "EngineComponentConfig.h"
#include "framework/GameTime.h"
#include "framework/Entity.h"
#include "framework/GameHeader.h"
#include "framework/GameConfig.h"
#include "framework/GameSpecification.h"
#include "framework/Game.h"
#include "EngineComponent.h"
#include "EngineConfig.h"
#include "Engine.h"

