#include "../gamelib.hpp"
#include "../kdebug.hpp"

void gamelibs::find_all() {
	engine = mem::module_find("./bin/engine.so");
	K_ASSERT(engine.is_valid());
	client = mem::module_find("./tf/bin/client.so");
	K_ASSERT(client.is_valid());
	sdl = mem::module_find("./bin/libSDL2-2.0.so.0");
	K_ASSERT(sdl.is_valid());
}
