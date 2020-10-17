#include "kisak.hpp"

#include <thread>

/* I am not entirely sure about creating new threads for installing/removing.      */
/* It *will* be nice to avoid freezing the process (from an end-user perspective), */
/* but this may invite race conditions later on. Perhaps sending a debugger break  */
/* to the game before installing hooks will prevent this? We'll see.               */

static void __attribute__((constructor)) load() {
	/* Detached threads. Nice. */
	std::thread runner(kisak_install);
	runner.detach();
}

static void __attribute__((destructor)) unload() {
	kisak_remove();
}
