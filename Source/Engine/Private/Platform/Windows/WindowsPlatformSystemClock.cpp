#include <Platform/Windows/WindowsPlatformSystemClock.h>

#include <Platform/Windows/WindowsBase.h>

namespace Neowise::Platform::Windows {
    CSystemClock GSystemClock = {};
    
    CSystemClock::CSystemClock() {
        TInt64 freq = {};
        queryPerformanceFrequency(freq);
        _frequency = 1 / TReal(freq);
        queryPerformanceCounter(_startTime);
    }

    TReal CSystemClock::getAbsoluteTimeMs() const {
        TInt64 now = {};
        queryPerformanceCounter(now);
        return TReal(now - _startTime) * _frequency;
    }

}
