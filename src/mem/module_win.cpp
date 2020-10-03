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

mem::Module::Module()
	: handle(nullptr), file_base_addr(0), code({}) {}


/* Locate a module in memory */
mem::Module::Module(const char* path) {
	this->handle = GetModuleHandle(path);
	this->file_base_addr = (std::uintptr_t)this->handle;

	/* The DOS header is right at the beginning of the PE file */
	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)this->handle;
	PIMAGE_NT_HEADERS nt_header  = (PIMAGE_NT_HEADERS)(this->file_base_addr + dos_header->e_lfanew);
	this->code.start = this->file_base_addr + nt_header->OptionalHeader.BaseOfCode;
	this->code.end   = this->code.start + nt_header->OptionalHeader.SizeOfCode;
}

/* Locate the address of a symbol in a module */
std::uintptr_t mem::Module::sym_addr(const char* sym) {
	return (std::uintptr_t)GetProcAddress((HMODULE)this->handle, sym);
}