#pragma once

#define CREATEINTERFACE_PROCNAME "CreateInterface"

namespace sdk {
	using create_iface_fn = void*(*)(const char* name, int* return_code);
}