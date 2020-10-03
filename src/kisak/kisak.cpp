#include "kisak.hpp"
#include "kdebug.hpp"
#include "gamelib.hpp"
#include "iface.hpp"
#include "graphics/graphics.hpp"

#include "mem/module.hpp"

/* Start the cheat */
void kisak_install() {
	K_LOG("kisak_install\n");

	gamelibs::find_all();
	K_LOG("Found all game libraries\n");

	iface::find_all();
	K_LOG("Found all game interfaces\n");

	K_LOG("engine lib: %p @ %p\n", gamelibs::engine.handle, gamelibs::engine.file_base);
	K_LOG("client lib: %p @ %p\n", gamelibs::client.handle, gamelibs::client.file_base);
	K_LOG("sdl lib:    %p @ %p\n", gamelibs::sdl.handle, gamelibs::sdl.file_base);

	K_LOG("engine iface: %p\n", (void*)iface::engine);

	graphics_init();
	K_LOG("Graphics initialized\n");

	/* mem::unload_self(); */
}

/* Shut down the cheat */
void kisak_remove() {
	K_LOG("kisak_remove\n");
}
