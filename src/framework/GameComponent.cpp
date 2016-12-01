/*
File: GameComponent.cpp
Author: Lars Vidar Magnusson
*/

#include <string.h>

#include <vector>
#include <unordered_map>

#include <v8.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>

#include "../lib/CStringHash.h"
#include "../lib/XercesUtils.h"
#include "../scripting/ScriptContext.h"
#include "../scripting/Script.h"
#include "GameTime.h"
#include "GameComponent.h"
#include "Game.h"
#include "../platform/PlatformConfig.h"
#include "../platform/Platform.h"
#include "../AddinInfo.h"
#include "../AddinContainer.h"
#include "../Addin.h"
#include "../EngineConfig.h"
#include "../Engine.h"


GameComponent *GameComponent::Create(Game *game, const char *typeName, const char *name) {

  return ENGINE->CreateGameComponent(game, typeName, name);

}

Game *GameComponent::GetGame() { return game; }
const char *GameComponent::GetName() { return name; }
