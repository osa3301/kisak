#pragma once

#include "vtable.hpp"
#include "../kconfig.hpp"

#include <memory>

#ifdef KISAK_WIN32
	#define VHOOK_DECL(class_type, name, ...) __fastcall name(class_type* _this, __VA_ARGS__)
#else
	#error VHOOK_DECL not defined
#endif

namespace mem {

	class VTableHook {
	public:
		VTableHook(vtable* cxx_class);
		~VTableHook();

		/* Replace an entry in the table */
		void replace(unsigned int idx, std::uintptr_t func);

		/* Get the real function address */
		std::uintptr_t get_real(unsigned int idx);
	private:
		unsigned int num_entries;
		vtable* cxx_class;
		vtable  real_table;
		std::unique_ptr<std::uintptr_t[]> user_table;
	};

}