#pragma once

#include <Base/MacroUtils.h>

#if NW_OS_TYPE_WIN32
#include "Windows/WindowsPlatformThread.h"

namespace Neowise::Platform {
    using Windows::CThread;
}

#elif NW_OS_TYPE_LINUX 
#include "Linux/LinuxPlatformThread.h"

namespace Neowise::Platform {
    using Linux::CThread;
}

#else
#include "Null/NullPlatformSystemClock.h"

namespace Neowise::Platform {
    using Null::CThread;
}

#endif
