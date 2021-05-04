#pragma once

#ifdef _WIN32
	#define ZEL_WINDOWS

	#ifdef _WIN64
		#define ZEL_WINDOWS_64
	#endif

#include "../platforms/windows/include/zel_windows_input_constants.h"
#endif