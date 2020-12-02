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

#include <windows.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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



namespace game {
    
    // Predeclarations

    class Engine;

    namespace framework {
        class System;
    }

}

#include "global.h"
#include "lib/string_util.h"
#include "lib/file_path.h"
#include "lib/command_line.h"
#include "lib/v8.h"
#include "graphics/vertex.h"
#include "graphics/model_view_projection.h"
#include "content/content.h"
#include "content/xml/xml_range.h"
#include "content/xml/xml_attribute.h"
#include "content/xml/xml_node.h"
#include "content/xml/xml_document.h"
#include "content/xml/xml_serializable.h"
#include "content/xml_content.h"
#include "graphics/image.h"
#include "graphics/vulkan//vulkan_functions.h"
#include "graphics/vulkan/shader.h"
#include "graphics/vulkan/vulkan.h"
#include "graphics/vulkan/texture.h"
#include "log.h"
#include "version.h"
#include "version_info.h"
#include "framework/framework.h"
#include "framework/system_info.h"
#include "framework/system_config.h"
#include "framework/component_info.h"

#include "addin/addin_header.h"
#include "addin/addin.h"
#include "scripting/script_environment.h"
#include "scripting/scriptable.h"
#include "scripting/script.h"

#include "platform/input_key.h"
#include "platform/platform_config.h"
#include "platform/platform.h"
#ifdef PLATFORM_WIN32VULKAN
#include "platform/win32_vulkan.h"
#endif
#ifdef PLATFORM_GLFWVULKAN
#include "platform/vulkan_platform.h"
#include "platform/glfw_vulkan_config.h"
#include "platform/glfw_vulkan.h"
#endif
#include "platform/default_platform.h"
#include "framework/game_time.h"
#include "framework/component_config.h"
#include "framework/component.h"
#include "framework/entity_specification.h"
#include "framework/entity.h"
#include "framework/game_header.h"
#include "framework/game_config.h"
#include "framework/game_specification.h"
#include "framework/game.h"
#include "framework/system.h"
#include "addin/system_provider.h"
#include "engine_config.h"
#include "engine.h"
