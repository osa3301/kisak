#include "mem/module.hpp"

#include <Windows.h>

/* https://devblogs.microsoft.com/oldnewthing/20041025-00/?p=37483             */
/* __ImageBase points to the beginning of the PE file in memory. This          */
/* pointer has the same value as the pointer returned from GetProcAddress(...) */
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static DWORD WINAPI unloader_func(LPVOID param) {
	HMODULE self = (HMODULE)&__ImageBase;

	FreeLibraryAndExitThread(self, 0);
}

/* Find a loaded module */
mem::Module mem::module_find(const char* name) {
	HMODULE result = GetModuleHandle(name);
	return mem::Module(result);
}

/* Get the address of an exported symbol */
void* mem::Module::sym_addr(const char* symbol) {
	return GetProcAddress((HMODULE)this->handle, symbol);
}

/* Special function to unload the calling code's module */
void mem::unload_self() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)unloader_func, NULL, 0, NULL);
}