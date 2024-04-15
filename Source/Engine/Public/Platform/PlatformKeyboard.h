#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformKeyboard.h"

namespace Neowise::Platform {
    using Windows::CKeyboard;
}

#elif NW_OS_TYPE_LINUX
#include "Linux/LinuxPlatformKeyboard.h"

namespace Neowise::Platform {
    using Linux::CKeyboard;
}

#else
#include "Null/NullPlatformKeyboard.h"

namespace Neowise::Platform {
    using Null::CKeyboard;
}

#endif

