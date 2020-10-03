#include "kisak.hpp"
#include "kdebug.hpp"
#include "gamelib.hpp"

#include "mem/module.hpp"

/* Start the cheat */
void kisak_install() {
	K_LOG("kisak_install\n");

	gamelibs::find_all();

	mem::unload_self();

	K_LOG("engine: %p\n", gamelibs::engine.handle);
	K_LOG("client: %p\n", gamelibs::client.handle);
}

/* Shut down the cheat */
void kisak_remove() {
	K_LOG("kisak_remove\n");
}