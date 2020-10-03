#include "kisak.hpp"
#include "kdebug.hpp"
#include "kconfig.hpp"
#include "gamemodule.hpp"
#include "iface.hpp"
#include "graphics/graphics.hpp"

/* Start the cheat */
void kisak_install() {
	K_DEBUG_INIT();
	K_LOG("kisak for %s (%s %s)\n", KISAK_GAME, __DATE__, __TIME__);

	gamemodule::find_all();
	iface::find_all();
	graphics::start();

	int width, height;
	iface::engine->get_screen_size(width, height);
	K_LOG("Screen size: (%d, %d)\n", width, height);

	K_LOG("Calling mem::unload_self()\n");
	/* mem::unload_self(); */
}

/* Shut down the cheat */
void kisak_remove() {
	K_LOG("Removing\n");

	K_DEBUG_SHUTDOWN();
}
