#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformSystemClock.h"

namespace Neowise::Platform {
    using Windows::GSystemClock;
}

#elif NW_OS_TYPE_LINUX
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
