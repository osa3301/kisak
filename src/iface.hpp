#pragma once

#include "sdk/sdk.hpp"

namespace iface {
	/* Find all required interfaces */
	void find_all();

	extern sdk::EngineClient* engine;
	extern sdk::InputSystem* input;
}