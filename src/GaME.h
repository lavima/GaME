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
#include <unordered_map>
#include <cassert>

using namespace std;

#include <v8.h>
#include <libplatform/libplatform.h>
#ifdef PLATFORM_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"
#include <windows.h>
#elif OS_WIN
#include <windows.h>
#endif
#ifdef PLATFORM_GLFW_VULKAN
#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#endif

#include <pugixml.hpp>

#include "util/StringUtil.h"
#include "util/FilePath.h"
#include "util/CommandLine.h"
#include "Log.h"
#include "lib/PugiXML.h"
#include "lib/Vulkan.h"
#include "Version.h"
#include "InfoBase.h"
#include "scripting/ScriptEnvironment.h"
#include "scripting/Scriptable.h"
#include "scripting/Script.h"
#include "lib/V8.h"
#include "platform/PlatformInfo.h"
#include "platform/PlatformConfig.h"
#include "platform/DefaultPlatformConfig.h"
#include "platform/Platform.h"
#ifdef PLATFORM_WIN32
#include "platform/Win32Vulkan.h"
#endif
#include "framework/GameTime.h"
#include "framework/Entity.h"
#include "framework/GameInfo.h"
#include "framework/GameConfig.h"
#include "framework/Game.h"
#include "AddinInfo.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "DefaultEngineConfig.h"
#include "EngineComponent.h"
#include "Engine.h"
#include "simplerenderer/SimpleRenderer.h"

