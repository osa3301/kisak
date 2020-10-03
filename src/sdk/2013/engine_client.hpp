#pragma once

#include "../util/impl.hpp"

/* https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/cdll_int.h */

#define VENGINE_CLIENT_INTERFACE_VERSION "VEngineClient013"

namespace sdk {

	class EngineClient {
	private:
		VFUNC_FILL(GetIntersectingSurfaces);
		VFUNC_FILL(GetLightForPoint);
		VFUNC_FILL(TraceLineMaterialAndLighting);
		VFUNC_FILL(ParseFile);
		VFUNC_FILL(CopyLocalFile);
	public:
		/* Gets the dimensions of the game window */
		virtual void get_screen_size(int& width, int& height) = 0;
	};

}