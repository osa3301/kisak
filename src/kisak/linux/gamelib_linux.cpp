#include "../gamelib.hpp"
#include "../kdebug.hpp"

void gamelibs::find_all() {
	engine = mem::module_find("./bin/engine.so");
	K_ASSERT(engine.is_valid());
	client = mem::module_find("./tf/bin/client.so");
	K_ASSERT(client.is_valid());
}
