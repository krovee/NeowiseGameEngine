#include <Platform/Null/NullPlatformSystemClock.h>

namespace Neowise::Platform::Null {
    CSystemClock GSystemClock = {};

    CSystemClock::CSystemClock() 
    {}

    TReal CSystemClock::getAbsoluteTimeMs() const {
        return 0;
    }

}
