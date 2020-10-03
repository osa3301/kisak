#include "gamemodule.hpp"
#include "kdebug.hpp"
#include "gamedata.hpp"

#ifdef KISAK_AGGRESSIVE_LOGGING
#define K_MODULE_ASSERT(x) K_LOG("%s loaded @ %p\n", #x, x); K_ASSERT(x)
#else
#define K_MODULE_ASSERT(x) K_ASSERT(x)
#endif

mem::module gamemodule::engine;
mem::module gamemodule::client;

void gamemodule::find_all() {
	engine = mem::module_find(GD_ENGINE_PATH);
	K_MODULE_ASSERT(engine);
	client = mem::module_find(GD_CLIENT_PATH);
	K_MODULE_ASSERT(client);
}