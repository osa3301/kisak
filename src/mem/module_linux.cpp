#include "mem/module.hpp"

#include <dlfcn.h>
#include <pthread.h>
#include <link.h>

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

mem::Module::Module(void* handle)
	: handle(handle) {

	file_base = ((link_map*)handle)->l_addr;
}

/* Get the address of an exported symbol */
std::uintptr_t mem::Module::sym_addr(const char* symbol) {
	return (std::uintptr_t)dlsym(this->handle, symbol);
}

/* Special function to unload the calling code's module */
void mem::unload_self() {
	/* Credit to Heep042 on UnknownCheats for popularizing this method */

	static int cool_data_not_on_stack = 0xB15B00B5;

	/* Get shared address info for a pointer in the calling library  */
	Dl_info info;
	if (!dladdr(&cool_data_not_on_stack, &info) || !info.dli_fname) {
		return;
	}

	mem::Module this_module = mem::module_find(info.dli_fname);
	if (!this_module.is_valid()) {
		return;
	}

	/* Create a thread at "dlclose" with the handle as the argument */
	pthread_t thread;
	pthread_create(&thread, NULL, (void*(*)(void*))dlclose, this_module.handle);
}
