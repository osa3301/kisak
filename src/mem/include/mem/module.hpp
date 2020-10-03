#pragma once

#include <cstddef>

namespace mem {

	/* OS-agnostic handle to a module */
	struct Module {
		Module()
			: handle(NULL) {}

		Module(void* handle)
			: handle(handle) {}

		inline bool is_valid() { return handle != NULL; }

		void* handle;
	};

	/* Find a loaded module */
	Module module_find(const char* name);

	/* Special function to unload the calling code's module */
	void unload_self();
}