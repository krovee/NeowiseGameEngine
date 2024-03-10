#pragma once

#if NW_OS_TYPE == NW_OS_TYPE_WIN32 
#include "Windows/WindowsPlatformKeyboard.h"

namespace Neowise::Platform {
	using Windows::CKeyboard;
}

#else
#include "Null/NullPlatformKeyboard.h"

namespace Neowise::Platform {
	using Null::CKeyboard;
}

#endif

