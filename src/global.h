#pragma once

#ifdef GAME_EXPORT
#define GAME_API __declspec(dllexport)
#elif GAME_IMPORT
#define GAME_API __declspec(dllimport)
#else
#define GAME_API 
#endif
