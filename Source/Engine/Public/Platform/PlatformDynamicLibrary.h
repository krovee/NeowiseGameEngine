#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformDynamicLibrary.h"

namespace Neowise::Platform {
	using Windows::CDynamicLibrary;
}

#elif NW_OS_TYPE_LINUX
#include "Linux/LinuxPlatformDynamicLibrary.h"

namespace Neowise::Platform {
	using Linux::CDynamicLibrary;
}

#else
#include "Null/NullPlatformDynamicLibrary.h"

namespace Neowise::Platform {
	using Null::CDynamicLibrary;
}

#endif
