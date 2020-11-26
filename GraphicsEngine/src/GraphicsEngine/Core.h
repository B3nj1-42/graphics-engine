#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GRAPHICS_ENGINE_API __declspec(dllexport)
	#else
		#define GRAPHICS_ENGINE_API __declspec(dllimport)
	#endif // GE_BUILD_DLL
#else
	#error The Graphics Engine only supports Windows!
#endif // GE_PLATFORM_WINDOWS

#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...)
	#define GE_CORE_ASSERT(x, ...)
#endif // GE_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1))