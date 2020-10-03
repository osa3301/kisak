#include "mem/module.hpp"

#include <dlfcn.h>

/* Find a loaded module */
mem::Module mem::module_find(const char* name) {
	/* Even though RTLD_NOLOAD is specified in this call,            */
	/* glibc's internal reference counter will still be incremented. */
	void* result = dlopen(name, RTLD_LAZY | RTLD_NOLOAD);
	if (result) {
		/* Decrement reference counter. If we don't do this, there */
		/* will be issues with unloading.                          */
		dlclose(result);
	}
	return mem::Module(result);
}

/* Get the address of an exported symbol */
void* mem::Module::sym_addr(const char* symbol) {
	return dlsym(this->handle, symbol);
}

/* Special function to unload the calling code's module */
void mem::unload_self() {
}
