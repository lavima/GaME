/*
* Filename: GaME.h
* Author: Lars Vidar Magnusson 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
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

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

#ifdef DLL_BUILD
#define GAME_API __declspec(dllexport)
#elif STATIC_BUILD
#define GAME_API 
#else
#define GAME_API __declspec(dllimport)
#endif


namespace game {
    using namespace std;
}

#include "lib/StringUtil.h"
#include "lib/FilePath.h"
#include "lib/CommandLine.h"
#include "lib/V8.h"
#include "graphics/Vertex.h"
#include "graphics/ModelViewProjection.h"
#include "data/Data.h"
#include "data/xml/XmlRange.h"
#include "data/xml/XmlAttribute.h"
#include "data/xml/XmlNode.h"
#include "data/xml/XmlDocument.h"
#include "data/xml/XmlSerializable.h"
#include "data/XmlData.h"
#include "graphics/Image.h"
#include "graphics/vulkan//VulkanFunctions.h"
#include "graphics/vulkan/Shader.h"
#include "graphics/vulkan/Vulkan.h"
#include "Log.h"
#include "Version.h"
#include "VersionInfo.h"
#include "SystemVersionInfo.h"
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
#include "SystemConfig.h"
#include "framework/GameTime.h"
#include "framework/Component.h"
#include "framework/Entity.h"
#include "framework/GameHeader.h"
#include "framework/GameConfig.h"
#include "framework/GameSpecification.h"
#include "framework/Game.h"
#include "System.h"
#include "EngineConfig.h"
#include "Engine.h"