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
	graphics::hook();
}

/* Shut down the cheat */
void kisak_remove() {
	K_LOG("Removing\n");

	K_DEBUG_SHUTDOWN();
}
