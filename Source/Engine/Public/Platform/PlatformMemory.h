#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformMemory.h"

namespace Neowise::Platform {
	using Windows::CMemory;
}

#elif NW_OS_TYPE_LINUX
#include "Linux/LinuxPlatformMemory.h"

namespace Neowise::Platform {
	using Linux::CMemory;
}

#else
#include "Null/NullPlatformMemory.h"

namespace Neowise::Platform {
	using Null::CMemory;
}

#endif
