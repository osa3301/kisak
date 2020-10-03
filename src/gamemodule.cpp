#include "gamemodule.hpp"
#include "kdebug.hpp"
#include "gamedata.hpp"

#ifdef KISAK_AGGRESSIVE_LOGGING
#define K_MODULE_ASSERT(x) K_LOG("%s loaded\t@ %p\n", #x, x.file_base()); K_ASSERT(x.is_valid())
#else
#define K_MODULE_ASSERT(x) K_ASSERT(x)
#endif

mem::Module gamemodule::engine;
mem::Module gamemodule::client;
mem::Module gamemodule::sdl;
#ifdef KISAK_WIN32
mem::Module gamemodule::shaderapi;
#endif
mem::Module gamemodule::inputsystem;

void gamemodule::find_all() {
	engine = mem::Module(GD_ENGINE_PATH);
	K_MODULE_ASSERT(engine);
	client = mem::Module(GD_CLIENT_PATH);
	K_MODULE_ASSERT(client);
	sdl = mem::Module(GD_SDL_PATH);
	K_MODULE_ASSERT(sdl);
#ifdef KISAK_WIN32
	shaderapi = mem::Module(GD_SHADER_API_PATH);
	K_MODULE_ASSERT(shaderapi);
#endif
	inputsystem = mem::Module(GD_INPUT_PATH);
	K_MODULE_ASSERT(inputsystem);
}
