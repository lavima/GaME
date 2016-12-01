/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#ifndef __SIMPLERENDERER_ADDIN__
#define __SIMPLERENDERER_ADDIN__

extern "C" {

void RegisterAddin(AddinInfo *addinInfo);

GameComponent *CreateGameComponent(Game *game, const char *typeName, const char *name);

}

#endif
