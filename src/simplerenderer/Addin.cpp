/*
File: Addin.cpp
Author: Lars Vidar Magnusson
*/

#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "../lib/CStringHash.h"
#include "../platform/PlatformConfig.h"
#include "../platform/Platform.h"
#include "../scripting/ScriptContext.h"
#include "../scripting/Script.h"
#include "../framework/GameTime.h"
#include "../framework/GameComponent.h"
#include "../framework/Game.h"
#include "../AddinInfo.h"
#include "../AddinContainer.h"
#include "../Addin.h"
#include "../EngineConfig.h"
#include "../Engine.h"
#include "Addin.h"
#include "SimpleRenderer.h"

void RegisterAddin(AddinInfo *addinInfo) {
  
  printf("Addin %s\n", addinInfo->GetName());

}

GameComponent *CreateGameComponent(Game *game, const char *typeName, const char *name) {

  return new SimpleRenderer(game);

}