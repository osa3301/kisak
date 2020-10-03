#include "graphics.hpp"

extern void graphics_init_platform();

void graphics::init() {
	graphics_init_platform();
}
