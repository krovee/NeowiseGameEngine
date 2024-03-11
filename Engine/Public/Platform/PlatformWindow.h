#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 
#include "Windows/WindowsPlatformWindow.h"

namespace Neowise::Platform {
	using Windows::CBaseWindow;
}

#else
#include "Null/NullPlatformWindow.h"

namespace Neowise::Platform {
	using Null::CBaseWindow;
}

#endif
