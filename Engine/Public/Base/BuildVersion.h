#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* Compile-time date-based version class.
	*/
	class NW_API CBuildVersion {
	public:
		CBuildVersion();

		operator uint64() const;
		uint64 get() const;
	private:
		uint64 _number = {};
	};

	/**
	* Engine dynamic library build version, encoded 
	* with date and time of compilation start.
	*/
	extern CBuildVersion buildVersion;
}
