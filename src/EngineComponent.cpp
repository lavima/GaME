/*
File: EngineComponent.cpp
Author: Lars Vidar Magnusson
*/

#include <string.h>

#include <vector>
#include <unordered_map>

#include <v8.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>

#include "lib/CStringHash.h"
#include "lib/Xerces.h"
#include "scripting/ScriptEnvironment.h"
#include "scripting/Script.h"
#include "framework/GameTime.h"
#include "framework/Game.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "AddinInfo.h"
#include "AddinContainer.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "EngineComponent.h"
#include "Engine.h"


CreateEngineComponentMap EngineComponent::createEngineComponentMap;

EngineComponent *EngineComponent::Create(const char *typeName, const char *name) {

  CreateEngineComponentMapIter item = createEngineComponentMap.find(typeName);
  if (item == createEngineComponentMap.end()) {
    printf("Could not find the specified game component type %s\n", typeName);
    return NULL;
  }
  CreateEngineComponentFun createEngineComponent = createEngineComponentMap[typeName];
  return createEngineComponent(ENGINE, typeName, name);

}