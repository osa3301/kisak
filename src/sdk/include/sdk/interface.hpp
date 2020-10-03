#pragma once

#define CREATEINTERFACE_PROCNAME "CreateInterface"

namespace tf2 {
	using create_iface_fn = void* (*)(const char* name, int* return_code);
}