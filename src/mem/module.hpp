#pragma once

#include <cstdint>

namespace mem {

	/* Handle to a module in memory */
	class Module {
	public:
		Module();
		Module(const char* path);

		/* Find the address of an exported symbol */
		std::uintptr_t sym_addr(const char* sym);

		/* Is a valid handle */
		inline bool is_valid() { return this->handle != nullptr; }

		/* Get the base address of the file in memory */
		inline std::uintptr_t file_base() { return this->file_base_addr; }

		/* Get the address of a code pattern */
		std::uintptr_t scan(const char* code);
	private:
		void* handle;
		std::uintptr_t file_base_addr;

		struct code_info {
			std::uintptr_t start;
			std::uintptr_t end;
		} code;
	};

	/* Special function to unload the module for the calling code */
	void unload_self();
}
