#pragma once

#include <Math/Scalar.h>

namespace Neowise {
    /** 
    * 16-bit floating point representation.
    */
    class NW_API half {
    public:
        ~half() = default;
        constexpr half() = default;
        half(TReal r);

        operator TReal() const;
        operator TInt16() const;
    private:
        TInt16 _rep = {};
    };
}
