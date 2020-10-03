#pragma once

#include "mem/module.hpp"
#include "kconfig.hpp"

namespace gamemodule {
	void find_all();

	extern mem::Module engine;
	extern mem::Module client;
	extern mem::Module sdl;
#ifdef KISAK_WIN32
	extern mem::Module shaderapi;
#endif
	extern mem::Module inputsystem;
}
