#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformWindow.h"

namespace Neowise::Platform {
	using Windows::CBaseWindow;
}

#elif NW_OS_TYPE_LINUX
#include "Linux/LinuxPlatformWindow.h"

namespace Neowise::Platform {
	using Linux::CBaseWindow;
}

#else
#include "Null/NullPlatformWindow.h"

namespace Neowise::Platform {
	using Null::CBaseWindow;
}

#endif
