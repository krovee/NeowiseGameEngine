#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* Universal-Unique-ID. Everyone should know it.
	*/
	class NW_API CUUID {
	public:
		CUUID();
		CUUID(uint64 initial);
		CUUID(const char* str);
		CUUID(const char* str, uint size);
		CUUID(const CUUID&);
		CUUID(CUUID&&);
		CUUID& operator=(const CUUID&);
		CUUID& operator=(CUUID&&);

		static const CUUID INVALID;

		const uint64 get64() const;
		const uint8  get8(uint64 i) const;

		operator uint64() const;

		bool operator==(const CUUID& r) const;
		bool operator!=(const CUUID& r) const;
		bool operator<(const CUUID& r) const;
		bool operator<=(const CUUID& r) const;
		bool operator>(const CUUID& r) const;
		bool operator>=(const CUUID& r) const;
	private:
		union {
			uint64		_b8 = {};
			struct {
				char	_0;
				char	_1;
				char	_2;
				char	_3;
				char	_4;
				char	_5;
				char	_6;
				char	_7;
			}			_b;
		};
	};
}
