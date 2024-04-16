#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>

namespace Neowise {
    /** 
    * Universal-Unique-ID. Everyone should know it.
    */
    class NW_API CUUID {
    public:
        CUUID();
        CUUID(TUint64 initial);
        CUUID(const char* str);
        CUUID(const char* str, TUint size);
        CUUID(const CUUID&);
        CUUID(CUUID&&);
        CUUID& operator=(const CUUID&);
        CUUID& operator=(CUUID&&);

        static const CUUID INVALID;

        TUint64 get64() const;
        TUint8  get8(TUint64 i) const;

        TUint8 operator[](TUint i) const;

        operator TUint() const;

        TBool operator==(const CUUID& r) const;
        TBool operator!=(const CUUID& r) const;
        TBool operator<(const CUUID& r) const;
        TBool operator<=(const CUUID& r) const;
        TBool operator>(const CUUID& r) const;
        TBool operator>=(const CUUID& r) const;
    private:
        union {
            TUint		_b8 = {};
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

    template<>
    class NW_API CObjectHash<CUUID> {
    public:
        static TUint get(const CUUID& uuid) {
            return TUint(uuid);
        }
    };
}
