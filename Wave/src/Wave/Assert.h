#pragma once

#include <cstdio>

namespace Wave {

#ifdef WAVE_DEBUG
	#define WAVE_DEBUGBREAK() __debugbreak();
#else
	#define WAVE_DEBUGBREAK()
#endif // WAVE_DEBUG

#ifdef WAVE_DEBUG
	#define WAVE_ASSERT(expr, msg, ...) { if (!(expr)) { printf(msg, __VA_ARGS__); printf("\n"); __debugbreak(); } }
#else
	#define WAVE_ASSERT(expr, msg, ...)
#endif // WAVE_DEBUG

}
