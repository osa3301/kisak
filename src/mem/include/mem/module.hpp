#pragma once

#include <cstdint>

namespace mem {

	/* OS-agnostic handle to a module */
	struct Module {
		Module()
			: handle(nullptr) {}

		Module(void* handle);

		inline bool is_valid() { return handle != nullptr; }

		/* Get the address of an exported symbol */
		std::uintptr_t sym_addr(const char* symbol);
		
		/* Get the pointer to an exported symbol */
		template <typename T>
		T sym_ptr(const char* symbol) {
			return (T)sym_addr(symbol);
		}

		void* handle;
		std::uintptr_t file_base;
	};

	/* Find a loaded module */
	Module module_find(const char* name);

	/* Special function to unload the calling code's module */
	void unload_self();
}
