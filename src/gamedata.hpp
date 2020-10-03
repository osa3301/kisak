#pragma once

#include "kconfig.hpp"

/* Module paths */

#ifdef KISAK_WIN32

#define GD_ENGINE_PATH		"engine.dll"
#define GD_CLIENT_PATH		"client.dll"
#define GD_SDL_PATH			"SDL2.dll"
#define GD_SHADER_API_PATH	"shaderapidx9.dll"
#define GD_INPUT_PATH		"inputsystem.dll"

#endif

#ifdef KISAK_LINUX

#define GD_ENGINE_PATH "./bin/engine.so"
#define GD_CLIENT_PATH "./tf/bin/client.so"
#define GD_SDL_PATH    "./bin/libSDL2-2.0.so.0"
#define GD_INPUT_PATH	"inputsystem.so"

#endif

/* Code patterns */

#ifdef KISAK_WIN32

#define GD_PAT_D3DDEVICE "FF 75 FC 8B 0D ? ? ? ?"

#endif
