#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>


#include <v8.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Log.h"
#include "lib/CommonTypes.h"
#include "lib/Xerces.h"
#include "scripting/ScriptEnvironment.h"
#include "scripting/Script.h"
#include "framework/GameTime.h"
#include "framework/Entity.h"
#include "framework/Game.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "AddinInfo.h"
#include "AddinContainer.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "EngineComponent.h"
#include "Engine.h"
#include "simplerenderer\SimpleRenderer.h"

using namespace std;