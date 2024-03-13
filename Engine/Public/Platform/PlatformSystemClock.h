#pragma once

#include <Base/MacroUtils.h>

#if NW_OS(WIN32) 
#include "Windows/WindowsPlatformSystemClock.h"

namespace Neowise::Platform {
	using Windows::GSystemClock;
}

#elif NW_OS(LINUX)
#include "Linux/LinuxPlatformSystemClock.h"

namespace Neowise::Platform {
	using Linux::GSystemClock;
}

#else
#include "Null/NullPlatformSystemClock.h"

namespace Neowise::Platform {
	using Null::GSystemClock;
}

#endif
