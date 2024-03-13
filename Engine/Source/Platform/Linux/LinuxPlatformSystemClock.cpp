#include <Platform/Linux/LinuxPlatformSystemClock.h>

#if NW_OS(LINUX)

#include <Platform/Linux/LinuxBase.h>

namespace Neowise::Platform::Linux {
    CSystemClock GSystemClock = {}; 
    
    CSystemClock::CSystemClock() {

    }

    real CSystemClock::getAbsoluteTimeMs() const {
        return _GetAbsoluteTime();
    }

}

#endif
