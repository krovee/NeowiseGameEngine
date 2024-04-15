#pragma once

#include <Base/NumericTypes.h>
#include <Base/StringView.h>
#include <Base/Templated.h>

namespace Neowise {
    enum : TUint64 {
        FNV64_PRIME		= 0x100000001b3ULL,
        FNV64_INITIAL	= 0xcbf29ce484222325ULL
    };

    /** 
    * Hashing algorithm utility class, based on FNV64-1a algorithm.
    */
    class NW_API CHash {
    public:
        CHash(TUint64 offset = FNV64_INITIAL);

        void offset(TUint64 value);

        TUint64 operator()(const CStringView& sv);
        TUint64 operator()(const char* str, TUint64 size);
        TUint64 operator()(const void* arr, TUint64 elemSize, TUint64 count);
    private:
        TUint64 _offset = {};
    };

    template<>
    class NW_API CObjectHash<CStringView> {
    public:
        static TUint get(const CStringView& sv) {
            return CHash()(sv);
        }
    };

}
