#include <Base/TimePoint.h>

namespace Neowise {
    CTimePoint::CTimePoint(TReal milliseconds)
        : _seconds(milliseconds)
    {
    }

    TReal CTimePoint::getMilliseconds() const {
        return _seconds * 1000;
    }

    TReal CTimePoint::getSeconds() const {
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
        if (ml < TReal(0.00001)) {
            return CTimePoint();
        }
        else {
            return CTimePoint(ml);
        }
    }

    CTimePoint& CTimePoint::normalize() {
        if (_seconds < TReal(0.00001)) {
            _seconds = 0;
        }
        return *this;
    }


}
