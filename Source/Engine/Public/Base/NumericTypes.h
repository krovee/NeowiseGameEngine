#pragma once

/**
* Defenition of every used numeric types of this codebase.
*/

#include <Base/Assert.h>

namespace Neowise {

    using TInt8     = signed char;
    using TInt16    = signed short;
    using TInt32    = signed int;
    using TInt64    = signed long long;
    
    using TUint8    = unsigned char;
    using TUint16   = unsigned short;
    using TUint32   = unsigned int;
    using TUint64   = unsigned long long;

    using TUint     = TUint64;

    using TPtrAddr  = unsigned long long;

    using TSingle   = float;
    using TDouble   = double;

    using TReal     = TSingle;

    using TBool     = bool;

    enum EBoolean : TBool {
        kFalse, // false
        kTrue,  // true
    };

    using TVaList   = void*;

    STATIC_ASSERT(sizeof(TInt8)     == 1);
    STATIC_ASSERT(sizeof(TUint8)    == 1);
    STATIC_ASSERT(sizeof(TInt16)    == 2);
    STATIC_ASSERT(sizeof(TUint16)   == 2);
    STATIC_ASSERT(sizeof(TInt32)    == 4);
    STATIC_ASSERT(sizeof(TUint32)   == 4);
    STATIC_ASSERT(sizeof(TInt64)    == 8);
    STATIC_ASSERT(sizeof(TUint)	    == 8);
    STATIC_ASSERT(sizeof(TUint64)   == 8);
    STATIC_ASSERT(sizeof(TPtrAddr)  == 8);
    STATIC_ASSERT(sizeof(TSingle)   == 4);
    STATIC_ASSERT(sizeof(TReal)     == 4);
    
    constexpr auto      __nullptraddr = TPtrAddr(0);
    #define nullptraddr __nullptraddr

    namespace Const {
        constexpr auto kMinI8       = TInt8     (-128);
        constexpr auto kMinI16      = TInt16    (-32768);
        constexpr auto kMinI32      = TInt32    (-2147483648);
        constexpr auto kMinI64      = TInt64    (-9223372036854775808ULL);
        constexpr auto kMaxI8       = TInt8     (128 - 1);
        constexpr auto kMaxI16      = TInt16    (32768 - 1);
        constexpr auto kMaxI32      = TInt32    (2147483648 - 1);
        constexpr auto kMaxI64      = TInt64    (9223372036854775807LL);
        constexpr auto kMinU8       = TUint8    (0);
        constexpr auto kMinU16      = TUint16   (0);
        constexpr auto kMinU32      = TUint32   (0);
        constexpr auto kMinU64      = TUint64   (0);
        constexpr auto kMaxU8       = TUint8    (0xff);
        constexpr auto kMaxU16      = TUint16   (0xffff);
        constexpr auto kMaxU32      = TUint32   (0xffffffff);
        constexpr auto kMaxU64      = TUint64   (0xffffffffffffffff);
        constexpr auto kRealInf     = TReal     (1e+38);
        constexpr auto kRealPi      = TReal     (3.1415926535);
        constexpr auto kReal2Pi     = TReal     (6.28318530718);
        constexpr auto kRealEps     = TReal     (1.192092896e-06); 
        constexpr auto kRealDeg2Rad = TReal     (0.01745329251);
        constexpr auto kRealRad2Deg = TReal     (57.2957795131);
    }

}
