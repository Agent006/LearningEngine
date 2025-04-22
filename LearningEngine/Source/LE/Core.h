
#pragma once

// ------

#ifdef LE_PLATFORM_WINDOWS
	#ifdef LE_BUILD_DLL
		#define LE_API __declspec(dllexport)
	#else
		#define LE_API __declspec(dllimport)
	#endif
#else
	#error Learning Engine only supports Windows!
#endif

// ------

#define BIT(x) (1 << x)

// ------

#ifdef LE_DEBUG
	#define LE_ENABLE_ASSERTS
#endif

#ifdef LE_ENABLE_ASSERTS
	#define LE_ASSERT(x, ...) { if ((x) == false) { LE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LE_CORE_ASSERT(x, ...) { if ((x) == false) { LE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LE_CORE_ASSERT(x) { if ((x) == false) { __debugbreak; } }
#else
	#define LE_ASSERT(x, ...)
	#define LE_CORE_ASSERT(x, ...)
	#define LE_CORE_ASSERT(x)
#endif

// ------

#define LE_BIND(ptr, fn) std::bind(fn, ptr, std::placeholders::_1)