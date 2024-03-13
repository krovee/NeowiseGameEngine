#include <Platform/Windows/WindowsPlatformSystemClock.h>

#if NW_OS(WIN32)

#include <Platform/Windows/WindowsBase.h>

namespace Neowise::Platform::Windows {
	CSystemClock GSystemClock = {};
	
	CSystemClock::CSystemClock() {
		int64 freq = {};
		queryPerformanceFrequency(freq);
		_frequency = 1 / real(freq);
		queryPerformanceCounter(_startTime);
	}

	real CSystemClock::getAbsoluteTimeMs() const {
		int64 now = {};
		queryPerformanceCounter(now);
		return real(now - _startTime) * _frequency;
	}

}

#endif
