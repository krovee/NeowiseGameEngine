#include <Base/UUID.h>
#include <Base/Hash.h>

namespace Neowise {
	static uint64 getUniqueID() {
		union _UUIDRep {
			struct {
				uint8	_0;
				uint8	_1;
				uint8	_2;
				uint8	_3;
				uint8	_4;
				uint8	_5;
				uint8	_6;
				uint8	_7;
			}			_b;
			uint64		_b8 = {};
		};
		static _UUIDRep rep = {
			{ __TIME__[0], __TIME__[1], __TIME__[2], __TIME__[3], __TIME__[4], __TIME__[5], __TIME__[6], __TIME__[7], }
		};

		rep._b._0 += '0' + int(real(rep._b._0) * 0.12421) % 70;
		rep._b._1 += '0' + int(real(rep._b._1) * 0.12411) % 70;
		rep._b._2 += '0' + int(real(rep._b._2) * 0.12421) % 70;
		rep._b._3 += '0' + int(real(rep._b._3) * 0.12431) % 70;
		rep._b._4 += '0' + int(real(rep._b._4) * 0.12441) % 70;
		rep._b._5 += '0' + int(real(rep._b._5) * 0.12451) % 70;
		rep._b._6 += '0' + int(real(rep._b._6) * 0.12461) % 70;
		rep._b._7 += '0' + int(real(rep._b._7) * 0.12471) % 70;

		return rep._b8;
	}

	const CUUID CUUID::INVALID = uint64(0);

	CUUID::CUUID() : _b8(getUniqueID())
	{}

	CUUID::CUUID(uint64 initial) : _b8(initial) {
	}

	CUUID::CUUID(const char* str) : _b8(CHash()(str)) {
	}

	CUUID::CUUID(const char* str, uint size) : _b8(CHash()({str, size}))
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

	const uint64 CUUID::get64() const {
		return _b8;
	}

	const uint8 CUUID::get8(uint64 i) const {
		return (&_b._0)[i];
	}

	CUUID::operator uint64() const {
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
