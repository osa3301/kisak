#include "module.hpp"

#include <dlfcn.h>
#include <link.h>

/* Special function to unload the module for the calling code */
void mem::unload_self() {
/*	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)unloader_func, NULL, 0, NULL); */
}

mem::Module::Module()
	: handle(nullptr) {}

mem::Module::Module(const char* path) {
	/* Even though RTLD_NOLOAD is specified, glibc's internal */
	/* reference counter is still incremented by this call.   */
	this->handle = dlopen(path, RTLD_LAZY | RTLD_NOLOAD);
	if (!this->is_valid()) {
		return;
	}

	/* If we don't do this, we will run into issues   */
	/* unloading later. */
	dlclose(this->handle);

	this->file_base_addr = ((link_map*)this->handle)->l_addr;
}

/* Find the address of an exported symbol */
std::uintptr_t mem::Module::sym_addr(const char* sym) {
	return (std::uintptr_t)dlsym(this->handle, sym);
}
