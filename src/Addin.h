/*
File: Addin.h
Author: Lars Vidar Magnusson
*/

#ifndef __ADDIN__
#define __ADDIN__

typedef void (*RegisterAddinFun)(AddinInfo *);
typedef GameComponent *(*CreateGameComponentFun)(Game *game, const char *, const char *);

#define ADDIN_REGISTERADDIN "RegisterAddin"
#define ADDIN_CREATECOMPONENT "CreateGameComponent"

#endif 
