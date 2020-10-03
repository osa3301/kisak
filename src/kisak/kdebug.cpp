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

void _kdebug::log(bool fatal, const char* fmt, ...) {
	if (!kdebug_logfile) {
		kdebug_logfile = std::fopen("kisak-debug.log", "w");
		if (!kdebug_logfile) {
			/* All hope is lost */
			return;
		}
	}

	/* Format argument list */
	char msg_buf[KDEBUG_MAX_MESSAGE];
	va_list args;
	va_start(args, fmt);
	std::vsnprintf(msg_buf, KDEBUG_MAX_MESSAGE, fmt, args);
	va_end(args);

	std::fprintf(kdebug_logfile, "%s", msg_buf);
	std::fflush(kdebug_logfile);

	/* Let the OS deal with closing the file handle */

#ifdef _WIN32
	if (fatal) {
		MessageBox(NULL, "Kisak - Fatal Error", msg_buf, MB_OK);
	}
#endif
}

void _kdebug::debug_break() {
#ifdef _WIN32
	DebugBreak();
#endif
}