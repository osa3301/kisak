#include "../gamelib.hpp"
#include "../kdebug.hpp"

void gamelibs::find_all() {
	engine = mem::module_find("engine.dll");
	K_ASSERT(engine.is_valid());
	client = mem::module_find("client.dll");
	K_ASSERT(client.is_valid());
}