#include "graphics.hpp"
#include "../kdebug.hpp"
#include "../gamelib.hpp"

#include "mem/hook.hpp"

#include <memory>

/* A lot of this is taken (with complete understanding :) ) from cathook */

/* SDL types */
using SDL_Window = struct {};
using SDL_GLContext = void*;

using SDL_GL_SwapWindow_fn = void(*)(SDL_Window*);

static SDL_GLContext	(*SDL_GL_GetCurrentContext)();
static SDL_GLContext	(*SDL_GL_CreateContext)(SDL_Window*);
static int		(*SDL_GL_MakeCurrent)(SDL_Window*, SDL_GLContext);

static std::unique_ptr<mem::SDLHook<SDL_GL_SwapWindow_fn>> swap_window_hook;

static SDL_GLContext game_context;
static SDL_GLContext kisak_context;

namespace hooks {

	/* Called on window update to swap the front and back GL buffers */
	static void SDL_GL_SwapWindow(SDL_Window* window) {

		static bool init = false;
		if (!init) {
			init = true;

			game_context = SDL_GL_GetCurrentContext();
			K_ASSERT(game_context);
			kisak_context = SDL_GL_CreateContext(window);
			K_ASSERT(kisak_context);
		}

		/* Switch to our context */
		SDL_GL_MakeCurrent(window, kisak_context);

		/* Do our rendering here */

		/* Switch back to the game context */
		SDL_GL_MakeCurrent(window, game_context);

		/* Call the original function */
		static auto original = swap_window_hook->get_original();
		return original(window);
	}
}

/* Initialize graphics hooks and contexts */
void graphics_init_platform() {
	/* Load SDL functions */
	SDL_GL_GetCurrentContext = gamelibs::sdl.sym_ptr<typeof(SDL_GL_GetCurrentContext)>("SDL_GL_GetCurrentContext");
	SDL_GL_CreateContext     = gamelibs::sdl.sym_ptr<typeof(SDL_GL_CreateContext)>("SDL_GL_CreateContext");
	SDL_GL_MakeCurrent       = gamelibs::sdl.sym_ptr<typeof(SDL_GL_MakeCurrent)>("SDL_GL_MakeCurrent");

	/* Get entry for SDL_GL_SwapWindow in the SDL jump table.   */
	/* I'm not sure of any more elegant way to accomplish this. */
	auto table_entry = (SDL_GL_SwapWindow_fn*)(gamelibs::sdl.file_base + 0xFD648);

	/* Install hook */
	swap_window_hook = std::make_unique<mem::SDLHook<SDL_GL_SwapWindow_fn>>(table_entry);
	swap_window_hook->apply(hooks::SDL_GL_SwapWindow);
}
