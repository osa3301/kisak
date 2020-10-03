#include "module.hpp"

#include <Windows.h>

/* https://devblogs.microsoft.com/oldnewthing/20041025-00/?p=37483             */
/* __ImageBase points to the beginning of the PE file in memory. This          */
/* pointer has the same value as the pointer returned from GetProcAddress(...) */
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static DWORD WINAPI unloader_func(LPVOID param) {
	HMODULE self = (HMODULE)&__ImageBase;

	FreeLibraryAndExitThread(self, 0);
}


/* Special function to unload the module for the calling code */
void mem::unload_self() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)unloader_func, NULL, 0, NULL);
}

/* Locate a module in memory */
mem::module mem::module_find(const char* name) {
	return GetModuleHandle(name);
}

/* Locate the address of a symbol in a module */
std::uintptr_t mem::module_sym_addr(module mod, const char* symbol) {
	return (std::uintptr_t)GetProcAddress((HMODULE)mod, symbol);
}