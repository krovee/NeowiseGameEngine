#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 
#include "Windows/WindowsPlatformMemory.h"

namespace Neowise::Platform {
	using Windows::CMemory;
}

#else
#include "Null/NullPlatformMemory.h"

namespace Neowise::Platform {
	using Null::CMemory;
}

#endif
