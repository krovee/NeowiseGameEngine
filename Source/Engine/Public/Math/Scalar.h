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
	NW_API real sin(real x);
	NW_API real dot(real x, real y);
	NW_API real cos(real x);
	NW_API real tan(real x);
	NW_API real asin(real x);
	NW_API real acos(real x);
	NW_API real atan(real x);
	NW_API real atan2(real y, real x);
	NW_API real sinh(real x);
	NW_API real cosh(real x);
	NW_API real tanh(real x);
	NW_API real asinh(real x);
	NW_API real acosh(real x);
	NW_API real atanh(real x);
	NW_API real pow(real base, real exp);
	NW_API real sqrt(real x);
	NW_API real cbrt(real x);
	NW_API real hypot(real x, real y);
	NW_API real rsqrt(real x);
	NW_API real modf(real arg, real* iptr);
	NW_API real fabs(real x);
	NW_API real fmod(real x, real y);
	NW_API real fma(real x, real y, real z);
	NW_API real log(real x);
	NW_API real log2(real x);
	NW_API real log10(real x);
	NW_API real ceil(real x);
	NW_API real floor(real x);
	NW_API real trunc(real x);
	NW_API real round(real x);
	NW_API real mix(real x, real y, real t);
}
