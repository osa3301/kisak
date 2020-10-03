#pragma once

#include "kconfig.hpp"

/* Module paths */

#ifdef KISAK_WIN32

#define GD_ENGINE_PATH "engine.dll"
#define GD_CLIENT_PATH "client.dll"

#endif

#ifdef KISAK_LINUX

#define GD_ENGINE_PATH "./bin/engine.so"
#define GD_CLIENT_PATH "./tf/bin/client.so"
#define GD_SDL_PATH "./bin/libSDL2-2.0.so.0"

#endif
