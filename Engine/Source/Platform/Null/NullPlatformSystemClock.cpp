#include <Platform/Null/NullPlatformSystemClock.h>

namespace Neowise::Platform::Null {
    CSystemClock GSystemClock = {};

    CSystemClock::CSystemClock() 
    {}

    uint64 CSystemClock::getAbsoluteTimeMs() const {
        return 0;
    }

}
