#pragma once

#include <Base/MacroUtils.h>

#if NW_OS(WIN32) 
#include "Windows/WindowsPlatformConsole.h"

namespace Neowise::Platform {
	using Windows::GConsole;
}

#elif NW_OS(LINUX)
#include "Linux/LinuxPlatformConsole.h"

namespace Neowise::Platform {
	using Linux::GConsole;
}

#else
#include "Null/NullPlatformConsole.h"

namespace Neowise::Platform {
	using Null::GConsole;
}

#endif
