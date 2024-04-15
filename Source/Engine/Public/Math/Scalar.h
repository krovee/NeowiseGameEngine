#pragma once

#include <Base/NumericTypes.h>

#include <immintrin.h>

#ifndef _mm_cvtss_i32_safe
#	if NW_OS_TYPE_LINUX
#		define _mm_cvtss_i32_safe __builtin_ia32_cvtss2si
#	else
#		define _mm_cvtss_i32_safe _mm_cvtss_i32
#	endif
#endif

/* 
* Common handy math scalar functions.
*/

namespace Neowise {
    NW_API TReal sin(TReal x);
    NW_API TReal dot(TReal x, TReal y);
    NW_API TReal cos(TReal x);
    NW_API TReal tan(TReal x);
    NW_API TReal asin(TReal x);
    NW_API TReal acos(TReal x);
    NW_API TReal atan(TReal x);
    NW_API TReal atan2(TReal y, TReal x);
    NW_API TReal sinh(TReal x);
    NW_API TReal cosh(TReal x);
    NW_API TReal tanh(TReal x);
    NW_API TReal asinh(TReal x);
    NW_API TReal acosh(TReal x);
    NW_API TReal atanh(TReal x);
    NW_API TReal pow(TReal base, TReal exp);
    NW_API TReal sqrt(TReal x);
    NW_API TReal cbrt(TReal x);
    NW_API TReal hypot(TReal x, TReal y);
    NW_API TReal rsqrt(TReal x);
    NW_API TReal modf(TReal arg, TReal* iptr);
    NW_API TReal fabs(TReal x);
    NW_API TReal fmod(TReal x, TReal y);
    NW_API TReal fma(TReal x, TReal y, TReal z);
    NW_API TReal log(TReal x);
    NW_API TReal log2(TReal x);
    NW_API TReal log10(TReal x);
    NW_API TReal ceil(TReal x);
    NW_API TReal floor(TReal x);
    NW_API TReal trunc(TReal x);
    NW_API TReal round(TReal x);
    NW_API TReal mix(TReal x, TReal y, TReal t);
}
