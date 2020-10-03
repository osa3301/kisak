#include "../kisak.hpp"

#include <thread>

#include <Windows.h>

/* I am not entirely sure about creating new threads for installing/removing.      */
/* It *will* be nice to avoid freezing the process (from an end-user perspective), */
/* but this may invite race conditions later on. We'll see.                        */

static void load() {
	/* Detached threads. Nice. */
	std::thread runner(kisak_install);
	runner.detach();
}

static void unload() {
	kisak_remove();
}

/* DllMain - Shared library entry point                        */
/* https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain */
BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		load();
		break;
	case DLL_PROCESS_DETACH:
		unload();
		break;
	}
	return TRUE;
}