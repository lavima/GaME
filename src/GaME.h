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
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#ifdef OS_WIN
#include <windows.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#endif

#include "util/Version.h"
#include "util/StringUtil.h"
#include "util/FilePath.h"
#include "util/CommandLine.h"
#include "Log.h"
#include "lib/CommonTypes.h"
#include "lib/Xerces.h"
#include "lib/Vulkan.h"
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
#include "simplerenderer\SimpleRenderer.h"
