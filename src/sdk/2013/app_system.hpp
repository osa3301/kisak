#pragma once

#include "../util/impl.hpp"

namespace sdk {
	class AppSystem {
	private:
		VFUNC_FILL(Connect);
		VFUNC_FILL(Disconnect);
		VFUNC_FILL(QueryInterface);
		VFUNC_FILL(Init);
		VFUNC_FILL(Shutdown);
	};
}