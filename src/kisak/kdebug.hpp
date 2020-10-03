#pragma once

namespace _kdebug {
	/* DO NOT CALL THIS DIRECTLY!!! Use the K_LOG_* macros instead. */
	void log(bool fatal, const char* fmt, ...);
	/* DO NOT CALL THIS DIRECTLY!!! Use the K_DEBUG_BREAK macro instead. */
	void debug_break();
};

/* TODO: Switch this on/off with CMake */
#if 1
	#define K_LOG(...) _kdebug::log(false, __VA_ARGS__)
	#define K_LOG_FATAL(...) _kdebug::log(true, __VA_ARGS__)
	#define K_DEBUG_BREAK() _kdebug::debug_break()
	#define K_ASSERT(x) if (x) {} else \
		{ K_LOG_FATAL("%s:%d ASSERT FAILED: %s\n", __FILE__, __LINE__, #x); K_DEBUG_BREAK(); }
#else
	#define K_LOG(...)
	#define K_LOG_FATAL(...)
	#define K_DEBUG_BREAK()
	#define K_ASSERT(x) { x; }
#endif