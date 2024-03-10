#pragma once

#include <Base/TimePoint.h>
#include <Platform/PlatformSystemClock.h>

namespace Neowise {

	/** 
	* Simple utility class for getting access to platform-specific system
	* clock. Measures in milliseconds.
	*/
	class CClock {
	public:
		static inline CTimePoint now() {
			return CTimePoint(Platform::GSystemClock.getAbsoluteTimeMs());
		}
	};
}
