#pragma once

#include <Base/Common.h>

namespace Neowise::Platform::Windows {
	/**
	*
	*/
	class NW_API CSystemClock {
	public:
		CSystemClock();

		real getAbsoluteTimeMs() const;

	private:
		int64 _startTime = {};
		real  _frequency = {};
	};

	extern CSystemClock GSystemClock;
}
