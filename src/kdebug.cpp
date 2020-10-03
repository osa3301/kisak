#include "kdebug.hpp"

/* MSVC "security features" can (and should) suck my balls */
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <cstdarg>

#ifdef _WIN32
	#include <Windows.h>
#endif

#define KDEBUG_MAX_MESSAGE 512

static std::FILE* kdebug_logfile = NULL;

void _kdebug::init() {
	kdebug_logfile = std::fopen("kisak-debug.log", "w");

#ifdef _WIN32
	/* Create a console to display stdout */
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif
}

void _kdebug::shutdown() {
	if (kdebug_logfile) {
		std::fclose(kdebug_logfile);
	}

#ifdef _WIN32
	FreeConsole();
#endif
}

void _kdebug::log(bool fatal, const char* fmt, ...) {
	if (!kdebug_logfile) {
		return;
	}

	/* Format argument list */
	char msg_buf[KDEBUG_MAX_MESSAGE];
	va_list args;
	va_start(args, fmt);
	std::vsnprintf(msg_buf, KDEBUG_MAX_MESSAGE, fmt, args);
	va_end(args);

	std::fprintf(kdebug_logfile, "%s", msg_buf);
	std::fflush(kdebug_logfile);

	std::printf("%s", msg_buf);

#ifdef _WIN32
	if (fatal) {
		MessageBox(NULL, msg_buf, "Kisak - Fatal Error", MB_OK);
	}
#endif
}

void _kdebug::debug_break() {
#ifdef _WIN32
	DebugBreak();
#endif
#ifdef __linux__
	__builtin_trap();
#endif
}
