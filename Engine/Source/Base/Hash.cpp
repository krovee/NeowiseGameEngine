#include <Base/Hash.h>

namespace Neowise {
	
	CHash::CHash(uint64 offset) 
		: _offset(offset)
	{
	}

	void CHash::offset(uint64 value) {
		_offset = value;
	}

	uint64 CHash::operator()(const CStringView& sv) {
		return operator()(sv.cstr(), sv.size());
	}

	uint64 CHash::operator()(const char* str, uint64 size) {
		auto bp = reinterpret_cast<const uint8*>(str);
		auto be = bp + size;

		auto hash = _offset;
		while (bp < be) {
			hash ^= static_cast<uint64>(*bp++);
			hash *= FNV64_PRIME;
		}

		return _offset = hash;
	}

	uint64 CHash::operator()(const void* arr, uint64 elemSize, uint64 count) {
		auto bp = reinterpret_cast<const uint8*>(arr);
		auto be = reinterpret_cast<const uint8*>(arr) + (elemSize * count);

		auto hash = _offset;
		while (bp < be) {
			hash ^= static_cast<uint64>(*bp++);
			hash *= FNV64_PRIME;
		}

		return _offset = hash;
	}


}
