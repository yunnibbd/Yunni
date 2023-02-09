#pragma once

#ifdef YN_PLATFORM_WINDOWS
	#ifdef YUNNI_BUILD_DLL
		#define YUNNI_API __declspec(dllexport)
	#else
		#define YUNNI_API __declspec(dllimport)
	#endif
#else
	#error Yunni only supports Windows!
#endif

#ifdef YN_ENABLE_ASSERTS
	#define YN_ASSERT(x, ...) { if(!(x)) {YN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define YN_CORE_ASSERT(x, ...) { if(!(x)) { YN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define YN_ASSERT(x, ...)
	#define YN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
