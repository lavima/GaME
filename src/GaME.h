/*
* Filename: GaME.h
* Author: Lars Vidar Magnusson 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

#include <v8.h>
#include <libplatform/libplatform.h>
#ifdef OS_WIN
#include <windows.h>
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>

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
#include "scripting/Script.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#ifdef OS_WIN
#include <windows.h>
#include "platform/Win32Vulkan.h"
#endif
#include "framework/GameTime.h"
#include "framework/Entity.h"
#include "framework/GameInfo.h"
#include "framework/Game.h"
#include "AddinInfo.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "EngineComponent.h"
#include "Engine.h"
#include "simplerenderer/SimpleRenderer.h"

