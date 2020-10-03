#include "gamemodule.hpp"
#include "kdebug.hpp"
#include "gamedata.hpp"

#ifdef KISAK_AGGRESSIVE_LOGGING
#define K_MODULE_ASSERT(x) K_LOG("%s loaded @ %p\n", #x, x); K_ASSERT(x)
#else
#define K_MODULE_ASSERT(x) K_ASSERT(x)
#endif

mem::Module gamemodule::engine;
mem::Module gamemodule::client;
mem::Module gamemodule::sdl;

void gamemodule::find_all() {
	engine = mem::Module(GD_ENGINE_PATH);
	K_MODULE_ASSERT(engine.is_valid());
	client = mem::Module(GD_CLIENT_PATH);
	K_MODULE_ASSERT(client.is_valid());
	sdl = mem::Module(GD_SDL_PATH);
	K_MODULE_ASSERT(sdl.is_valid());
}
