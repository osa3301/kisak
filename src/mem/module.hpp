#pragma once

#include <cstdint>

namespace mem {

	using module = void*;

	/* Special function to unload the module for the calling code */
	void unload_self();

	/* Locate a module in memory */
	module module_find(const char* name);

	/* Locate the address of a symbol in a module */
	std::uintptr_t module_sym_addr(module mod, const char* symbol);

}