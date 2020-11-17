#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GRAPHICS_ENGINE_API __declspec(dllexport)
	#else
		#define GRAPHICS_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error The Graphics Engine only supports Windows!
#endif