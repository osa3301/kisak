#include "iface.hpp"
#include "gamemodule.hpp"
#include "kdebug.hpp"

#ifdef KISAK_AGGRESSIVE_LOGGING
#define K_IFACE_ASSERT(x) K_LOG("iface %s @ %p\n", #x, x); K_ASSERT(x)
#else
#define K_IFACE_ASSERT(x) K_ASSERT(x)
#endif

sdk::EngineClient* iface::engine = nullptr;

static sdk::create_iface_fn find_factory(mem::module& mod) {
	return (sdk::create_iface_fn)mem::module_sym_addr(mod, CREATEINTERFACE_PROCNAME);
}

/* Find all required interfaces */
void iface::find_all() {
	static auto engine_factory = find_factory(gamemodule::engine);
	K_ASSERT(engine_factory);
	static auto client_factory = find_factory(gamemodule::client);
	K_ASSERT(client_factory);

	engine = (sdk::EngineClient*)engine_factory(VENGINE_CLIENT_INTERFACE_VERSION, nullptr);
	K_IFACE_ASSERT(engine);
}