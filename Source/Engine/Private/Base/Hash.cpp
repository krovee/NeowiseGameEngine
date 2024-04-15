#include <Base/Hash.h>

namespace Neowise {
    
    CHash::CHash(TUint64 offset) 
        : _offset(offset)
    {
    }

    void CHash::offset(TUint64 value) {
        _offset = value;
    }

    TUint64 CHash::operator()(const CStringView& sv) {
        return operator()(sv.cstr(), sv.size());
    }

    TUint64 CHash::operator()(const char* str, TUint64 size) {
        auto bp = reinterpret_cast<const TUint8*>(str);
        auto be = bp + size;

        auto hash = _offset;
        while (bp < be) {
            hash ^= static_cast<TUint64>(*bp++);
            hash *= FNV64_PRIME;
        }

        return _offset = hash;
    }

    TUint64 CHash::operator()(const void* arr, TUint64 elemSize, TUint64 count) {
        auto bp = reinterpret_cast<const TUint8*>(arr);
        auto be = reinterpret_cast<const TUint8*>(arr) + (elemSize * count);

        auto hash = _offset;
        while (bp < be) {
            hash ^= static_cast<TUint64>(*bp++);
            hash *= FNV64_PRIME;
        }

        return _offset = hash;
    }


}
