#include "kisak.hpp"
#include "kdebug.hpp"
#include "gamelib.hpp"
#include "iface.hpp"

#include "mem/module.hpp"

/* Start the cheat */
void kisak_install() {
	K_LOG("kisak_install\n");

	gamelibs::find_all();
	K_LOG("Found all game libraries\n");

	iface::find_all();
	K_LOG("Found all game interfaces\n");

	K_LOG("engine lib: %p\n", gamelibs::engine.handle);
	K_LOG("client lib: %p\n", gamelibs::client.handle);

	K_LOG("engine iface: %p\n", (void*)iface::engine);

	mem::unload_self();
}

/* Shut down the cheat */
void kisak_remove() {
	K_LOG("kisak_remove\n");
}