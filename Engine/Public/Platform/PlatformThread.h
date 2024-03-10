#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 
#include "Windows/WindowsPlatformThread.h"

namespace Neowise::Platform {
	using Windows::CThread;
}

#else
#include "Null/NullPlatformSystemClock.h"

namespace Neowise::Platform {
	using Null::CThread;
}

#endif
