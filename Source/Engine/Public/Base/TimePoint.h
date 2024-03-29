#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* Handy class for time mesurements. 
	*/
	class NW_API CTimePoint {
	public:
		CTimePoint(real milliseconds = 0);

		CTimePoint(const CTimePoint&) = default;
		CTimePoint(CTimePoint&&) = default;
		CTimePoint& operator=(const CTimePoint&) = default;
		CTimePoint& operator=(CTimePoint&&) = default;
		
		real getMilliseconds() const;
		real getSeconds() const;

		bool operator==(const CTimePoint& r) const;
		bool operator!=(const CTimePoint& r) const;
		bool operator<(const CTimePoint& r) const;
		bool operator>(const CTimePoint& r) const;
		bool operator<=(const CTimePoint& r) const;
		bool operator>=(const CTimePoint& r) const;

		CTimePoint operator-(const CTimePoint& r) const;

		/** 
		* 
		*/
		static CTimePoint normalize(const CTimePoint& tp);
		CTimePoint& normalize();
	private:
		real _seconds = {};
	};
}
