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

#define BIT(x) (1 << x)
