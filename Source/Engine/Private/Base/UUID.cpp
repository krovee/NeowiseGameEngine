#include <Base/UUID.h>
#include <Base/Hash.h>

namespace Neowise {
    static TUint64 getUniqueID() {
        union _UUIDRep {
            struct {
                TUint8	_0;
                TUint8	_1;
                TUint8	_2;
                TUint8	_3;
                TUint8	_4;
                TUint8	_5;
                TUint8	_6;
                TUint8	_7;
            }			_b;
            TUint64		_b8 = {};
        };
        static _UUIDRep rep = {
            { __TIME__[0], __TIME__[1], __TIME__[2], __TIME__[3], __TIME__[4], __TIME__[5], __TIME__[6], __TIME__[7], }
        };

        rep._b._0 += '0' + int(TReal(rep._b._0) * 0.12421) % 70;
        rep._b._1 += '0' + int(TReal(rep._b._1) * 0.12411) % 70;
        rep._b._2 += '0' + int(TReal(rep._b._2) * 0.12421) % 70;
        rep._b._3 += '0' + int(TReal(rep._b._3) * 0.12431) % 70;
        rep._b._4 += '0' + int(TReal(rep._b._4) * 0.12441) % 70;
        rep._b._5 += '0' + int(TReal(rep._b._5) * 0.12451) % 70;
        rep._b._6 += '0' + int(TReal(rep._b._6) * 0.12461) % 70;
        rep._b._7 += '0' + int(TReal(rep._b._7) * 0.12471) % 70;

        return rep._b8;
    }

    const CUUID CUUID::INVALID = TUint64(0);

    CUUID::CUUID() : _b8(getUniqueID())
    {}

    CUUID::CUUID(TUint64 initial) : _b8(initial) {
    }

    CUUID::CUUID(const char* str) : _b8(CHash()(str)) {
    }

    CUUID::CUUID(const char* str, TUint size) : _b8(CHash()({str, size}))
    {
    }

    CUUID::CUUID(const CUUID& o) : _b8(o._b8) {
    }

    CUUID::CUUID(CUUID&& o) : _b8(o._b8) {
        o = INVALID;
    }

    CUUID& CUUID::operator=(const CUUID& r) {
        _b8 = r._b8;
        return *this;
    }

    CUUID& CUUID::operator=(CUUID&& r) {
        _b8 = r._b8;
        r = INVALID;
        return *this;
    }

    TUint64 CUUID::get64() const {
        return _b8;
    }

    TUint8 CUUID::get8(TUint64 i) const {
        return (&_b._0)[i];
    }

    TUint8 Neowise::CUUID::operator[](TUint i) const {
        return (&_b._0)[i];
    }

    CUUID::operator TUint() const {
        return _b8;
    }

    bool CUUID::operator==(const CUUID& r) const {
        return _b8 == r._b8;
    }

    bool CUUID::operator!=(const CUUID& r) const {
        return _b8 != r._b8;
    }

    bool CUUID::operator<(const CUUID& r) const {
        return _b8 < r._b8;
    }
    
    bool CUUID::operator<=(const CUUID& r) const {
        return _b8 <= r._b8;
    }
    
    bool CUUID::operator>(const CUUID& r) const {
        return _b8 > r._b8;
    }
    
    bool CUUID::operator>=(const CUUID& r) const {
        return _b8 >= r._b8;
    }

}
