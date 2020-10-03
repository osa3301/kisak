#include "iface.hpp"
#include "gamelib.hpp"
#include "kdebug.hpp"

#include "sdk/interface.hpp"

#include <cstddef>

tf2::EngineClient* iface::engine = nullptr;

void iface::find_all() {
	tf2::create_iface_fn engine_factory = gamelibs::engine.sym_ptr<tf2::create_iface_fn>(CREATEINTERFACE_PROCNAME);
	K_ASSERT(engine_factory);
	tf2::create_iface_fn client_factory = gamelibs::client.sym_ptr<tf2::create_iface_fn>(CREATEINTERFACE_PROCNAME);
	K_ASSERT(client_factory);

	iface::engine = (tf2::EngineClient*)engine_factory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
	K_ASSERT(iface::engine);
}