#include <Base/TimePoint.h>

namespace Neowise {
	CTimePoint::CTimePoint(real milliseconds)
		: _seconds(milliseconds)
	{
	}

	real CTimePoint::getMilliseconds() const {
		return _seconds * 1000;
	}

	real CTimePoint::getSeconds() const {
		return _seconds;
	}

	bool CTimePoint::operator==(const CTimePoint& r) const {
		return _seconds == r._seconds;
	}

	bool CTimePoint::operator!=(const CTimePoint& r) const {
		return _seconds != r._seconds;
	}

	bool CTimePoint::operator<(const CTimePoint& r) const {
		return _seconds < r._seconds;
	}

	bool CTimePoint::operator>(const CTimePoint& r) const {
		return _seconds > r._seconds;
	}

	bool CTimePoint::operator<=(const CTimePoint& r) const {
		return _seconds <= r._seconds;
	}

	bool CTimePoint::operator>=(const CTimePoint& r) const {
		return _seconds >= r._seconds;
	}

	CTimePoint CTimePoint::operator-(const CTimePoint& r) const {
		return CTimePoint(_seconds - r._seconds);
	}

	CTimePoint CTimePoint::normalize(const CTimePoint& tp) {
		const auto& ml = tp._seconds;
		if (ml < real(0.00001)) {
			return CTimePoint();
		}
		else {
			return CTimePoint(ml);
		}
	}

	CTimePoint& CTimePoint::normalize() {
		if (_seconds < real(0.00001)) {
			_seconds = 0;
		}
		return *this;
	}


}
