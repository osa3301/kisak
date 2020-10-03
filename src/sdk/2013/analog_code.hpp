#pragma once

namespace sdk {
	
	enum AnalogCode {
		ANALOG_CODE_INVALID = -1,
		MOUSE_X = 0,
		MOUSE_Y,
		MOUSE_XY,		// Invoked when either x or y changes
		MOUSE_WHEEL,
	};

}