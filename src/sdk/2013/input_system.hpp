#pragma once

#include "../util/impl.hpp"
#include "button_code.hpp"
#include "analog_code.hpp"
#include "app_system.hpp"

#define INPUTSYSTEM_INTERFACE_VERSION	"InputSystemVersion001"

namespace sdk {
	class InputSystem : public AppSystem {
	private:
		VFUNC_FILL(AttachToWindow);
		VFUNC_FILL(DetachFromWindow);
		VFUNC_FILL(EnableInput);
		VFUNC_FILL(EnableMessagePump);
		VFUNC_FILL(PollInputState);
		VFUNC_FILL(GetPollTick);
	public:
		/* Is a button down? "Buttons" are binary-state input devices (mouse buttons, keyboard keys) */
		virtual bool is_button_down(ButtonCode code) const = 0;
		/* Returns the tick at which the button was pressed */
		virtual int get_button_pressed_tick(ButtonCode code) const = 0;
		/* Returns the tick at which the button was released */
		virtual int get_button_released_tick(ButtonCode code) const = 0;
		/* Gets the value of an analog input device this frame */
		/* Includes joysticks, mousewheel, mouse */
		virtual int get_analog_value(AnalogCode code) const = 0;
	};
}