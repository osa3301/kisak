#pragma once

#include <cstdint>

namespace mem {

	using vtable = std::uintptr_t*;

	template <typename T>
	inline vtable& vtable_get(T cxx_class) {
		return *(vtable*)cxx_class;
	}

}