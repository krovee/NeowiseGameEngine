#pragma once

#include <Base/MacroUtils.h>

namespace Neowise {

    /**
    * macro STATIC_ASSERT implemented through simple
    * technique with template polymorphism. If compile
    * time condition is TRUE, so everything is OK, otherwise
    * SCompileTimeAssert<cond> won't find suitable type,
    * and compile time error will throw.
    */

#ifndef STATIC_ASSERT
    template<bool>
    struct SCompileTimeAssert 
    {
    };

    template<>
    struct SCompileTimeAssert<true> {
        using TCtFail = int;
    };

#define STATIC_ASSERT(cond) \
    static inline typename Neowise::SCompileTimeAssert<!!(cond)>::TCtFail NW_CONCAT(__hiddenComptimeCheck, __LINE__){}
#endif

#ifdef  NW_SHIP_BUILD
#   undef  STATIC_ASSERT
#   define STATIC_ASSERT(cond) 
#endif

    /**
    * Runtime assert message call, used to output message, and stop program run.
    */
    NW_API void Assert(const char* msg, const char* fnname, const char* file, const int line);

#ifndef NW_ASSERT
#   define NW_ASSERT(cond, msg)                                 \
    do {                                                        \
        if (!(cond)) {                                          \
            Assert((msg), __FUNCTION__, __FILE__, __LINE__);    \
        }                                                       \
    } while (0)
#endif

    /**
    * In shipped code we don't want to provide any assertion
    * since they're slow down runtime dramatically.
    */

#ifdef  NW_SHIP_BUILD
#   undef  NW_ASSERT
#   define NW_ASSERT(cond, msg) (void)0
#endif

    /**
    * Optional assertation is used to check and output message
    * if some condition _SHOULD_ be TRUE, but it not and this
    * is not so critical.
    */

#ifndef NW_OPT_ASSERT
#   define NW_OPT_ASSERT(cond, msg) \
    Neowise::ignoreAssert(kTrue);    \
    NW_ASSERT(cond, msg);           \
    Neowise::ignoreAssert(kFalse) 
#endif

#ifdef  NW_SHIP_BUILD
#   undef  NW_OPT_ASSERT
#   define NW_OPT_ASSERT(cond, msg) (void)0
#endif

}
