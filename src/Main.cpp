/*
File: Main.cpp
Author: Lars Vidar Magnusson
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <v8.h>
#include <xercesc/dom/DOM.hpp>

#include <vector>
#include <unordered_map>

#include "lib/CStringHash.h"
#include "platform/PlatformConfig.h"
#include "platform/Platform.h"
#include "scripting/ScriptContext.h"
#include "scripting/Script.h"
#include "framework/GameTime.h"
#include "framework/GameComponent.h"
#include "framework/Game.h"
#include "AddinInfo.h"
#include "AddinContainer.h"
#include "Addin.h"
#include "EngineConfig.h"
#include "Engine.h"

/*
 * Program entry.
 * 
 * Usage: game ENGINECONFIG GAMESPEC
 */
int main(int argc, const char *argv[]) {

  if (argc != 3) {
    printf("Usage: game ENGINECONFIG GAMESPEC\n");
    return 1;
  }

  ENGINE->Initialize(argv[1]);

  ENGINE->RunGame(argv[2]);

  return 0;
}
