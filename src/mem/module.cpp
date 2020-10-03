#include "module.hpp"
#include "../kdebug.hpp"

template <typename T>
static bool in_range(T x, T a, T b) {
	return x >= a && x <= b;
}

/* char -> byte */
static std::uint8_t char_to_byte(const char c) {
	/* [A, F] */
	if (in_range<char>(c & (~0x20), 'A', 'F')) {
		return (c & (~0x20)) - 'A' + 0xA;
	}
	else {
		/* [0, 9] */
		if (in_range<char>(c, '0', '9')) {
			return c - '0';
		}
		else {
			return 0;
		}
	}
}

/* Convert an ASCII string (ex. "A3" or "6E") to an actual byte */
static std::uint8_t str_to_byte(const char* pat) {
	return char_to_byte(pat[0]) << 4 | char_to_byte(pat[1]);
}

/* Get the address of a code pattern */
std::uintptr_t mem::Module::scan(const char* code) {
	/* I believe this algorithm was originally written by learn_more */
	const char* pattern = code;
	std::uintptr_t match = 0;

	for (std::uintptr_t cur = this->code.start; cur < this->code.end; ++cur) {
		if (pattern[0] == '\0') {
			return match;
		}

		const std::uint8_t& b = *(std::uint8_t*)cur;

		if (pattern[0] == '?' || str_to_byte(pattern) == b) {
			if (match == 0) {
				match = cur;
			}
			if (pattern[2] == '\0') {
				return match;
			}
			pattern += (pattern[0] == '?') ? 2 : 3;
		} else {
			pattern = code;
			match = 0;
		}
	}

	K_LOG_FATAL("Could not find code pattern %s\n", code);
	return 0;
}