#pragma once

#include <Base/Common.h>

namespace Neowise::Platform::Null {
	/** 
	* 
	*/
	class NW_API CSystemClock {
	public:
		CSystemClock();

		uint64 getAbsoluteTimeMs() const;
	};
	
	extern CSystemClock GSystemClock;
}
