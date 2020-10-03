#include "graphics.hpp"
#include "../kdebug.hpp"
#include "../gamemodule.hpp"

#include <memory>

/* A lot of this is taken (with complete understanding :) ) from cathook */

/* Hook a function by replacing its entry in the */
/* SDL jump table. */
template <typename Fn>
class SDLHook {
public:
	SDLHook(Fn* table_entry)
		: hooked(false), table_entry(table_entry),
		  original_entry(*table_entry) {}
	~SDLHook() {
		if (hooked) {
			*table_entry = original_entry;
			hooked = false;
		}
	}

	void apply(Fn user_entry) {
		*table_entry = user_entry;
		hooked = true;
	}

	Fn get_original() {
		return original_entry;
	}
private:
	bool hooked;
	Fn*  table_entry;
	Fn   original_entry;
};

/* SDL types */
using SDL_Window = struct {};
using SDL_GLContext = void*;

using SDL_GL_SwapWindow_fn = void(*)(SDL_Window*);

static SDL_GLContext	(*SDL_GL_GetCurrentContext)();
static SDL_GLContext	(*SDL_GL_CreateContext)(SDL_Window*);
static int		(*SDL_GL_MakeCurrent)(SDL_Window*, SDL_GLContext);

static std::unique_ptr<SDLHook<SDL_GL_SwapWindow_fn>> swap_window_hook;

static SDL_GLContext game_context;
static SDL_GLContext kisak_context;

namespace hooks {

	/* Called on window update to swap the front and back GL buffers */
	static void SDL_GL_SwapWindow(SDL_Window* window) {

		K_LOG("SDL_GL_SwapWindow\n");

		/* Call the original function */
		static auto original = swap_window_hook->get_original();
		return original(window);
	}

}

void graphics_init_platform() {
	/* Load SDL functions */
	SDL_GL_GetCurrentContext = (typeof(SDL_GL_GetCurrentContext))gamemodule::sdl.sym_addr("SDL_GL_GetCurrentContext");
	SDL_GL_CreateContext     = (typeof(SDL_GL_CreateContext))gamemodule::sdl.sym_addr("SDL_GL_CreateContext");
	SDL_GL_MakeCurrent       = (typeof(SDL_GL_MakeCurrent))gamemodule::sdl.sym_addr("SDL_GL_MakeCurrent");

	/* Get entry for SDL_GL_SwapWindow in the SDL jump table.    */
	/* I'm not sure of a more elegant way of accomplishing this. */
	auto table_entry = (SDL_GL_SwapWindow_fn*)(gamemodule::sdl.file_base() + 0xFD648);
	K_LOG("SDL_GL_SwapWindow jump table entry: %p\n", (void*)table_entry);

	/* Install hook */
	swap_window_hook = std::make_unique<SDLHook<SDL_GL_SwapWindow_fn>>(table_entry);
	swap_window_hook->apply(hooks::SDL_GL_SwapWindow);
}
