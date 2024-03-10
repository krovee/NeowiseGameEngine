#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 
#include "Windows/WindowsPlatformSystemClock.h"

namespace Neowise::Platform {
	using Windows::GSystemClock;
}

#else
#include "Null/NullPlatformSystemClock.h"

namespace Neowise::Platform {
	using Null::GSystemClock;
}

#endif
