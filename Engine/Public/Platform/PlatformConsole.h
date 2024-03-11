#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 

#include "Windows/WindowsPlatformConsole.h"

namespace Neowise::Platform {
	using Windows::CConsole;
}

#else
#include "Null/NullPlatformConsole.h"

namespace Neowise::Platform {
	using Null::CConsole;
}

#endif

namespace Neowise::Platform {
	extern CConsole GConsole;
}
