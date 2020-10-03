#include "hook.hpp"
#include "../kdebug.hpp"

#include <cstring>

mem::VTableHook::VTableHook(mem::vtable* cxx_class)
	: cxx_class(cxx_class), real_table(*cxx_class), num_entries(0) {

	/* Count vtable entries */
	while (real_table[num_entries]) {
		++num_entries;
	}

	K_ASSERT(num_entries > 0);

	/* Clone table */
	user_table = std::make_unique<std::uintptr_t[]>(num_entries);
	std::memcpy(user_table.get(), real_table, num_entries * sizeof(std::uintptr_t));

	/* Swap pointer */
	*cxx_class = user_table.get();
}

mem::VTableHook::~VTableHook() {
	/* Swap pointer */
	*cxx_class = real_table;
}

/* Replace an entry in the table */
void mem::VTableHook::replace(unsigned int idx, std::uintptr_t func) {
	K_ASSERT(idx < num_entries);
	user_table[idx] = func;
}

/* Get the real function address */
std::uintptr_t mem::VTableHook::get_real(unsigned int idx) {
	K_ASSERT(idx < num_entries);
	return real_table[idx];
}
