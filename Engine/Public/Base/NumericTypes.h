#pragma once

/**
* Defenition of every used numeric types of this codebase.
*/

#include "MacroUtils.h"
#include "Assert.h"

namespace Neowise {

	using int8		= signed char;
	using int16		= signed short;
	using int32		= signed int;
	using int64		= signed long long;
	
	using uint8		= unsigned char;
	using uint16	= unsigned short;
	using uint32	= unsigned int;
	using uint64	= unsigned long long;

	using uint		= uint64;

	using ptraddr	= unsigned long long;

	using single	= float;

	using real		= single;

	using vaList = void*;

	STATIC_ASSERT(sizeof(int8)		== 1);
	STATIC_ASSERT(sizeof(uint8)		== 1);
	STATIC_ASSERT(sizeof(int16)		== 2);
	STATIC_ASSERT(sizeof(uint16)	== 2);
	STATIC_ASSERT(sizeof(int32)		== 4);
	STATIC_ASSERT(sizeof(uint32)	== 4);
	STATIC_ASSERT(sizeof(int64)		== 8);
	STATIC_ASSERT(sizeof(uint)		== 8);
	STATIC_ASSERT(sizeof(uint64)	== 8);
	STATIC_ASSERT(sizeof(ptraddr)	== 8);
	STATIC_ASSERT(sizeof(single)	== 4);
	STATIC_ASSERT(sizeof(real)		== 4);
	
	constexpr auto __nullptraddr = ptraddr(-1);
	#define nullptraddr __nullptraddr

	namespace Const {
		constexpr auto INT8_MIN		= int8(-128);
		constexpr auto INT16_MIN	= int16(-32768);
		constexpr auto INT32_MIN	= int32(-2147483648);
		constexpr auto INT64_MIN	= int64(-9223372036854775808ULL);
		constexpr auto INT8_MAX		= int8(128 - 1);
		constexpr auto INT16_MAX	= int16(32768 - 1);
		constexpr auto INT32_MAX	= int32(2147483648 - 1);
		constexpr auto INT64_MAX	= int64(9223372036854775807LL);
		constexpr auto UINT8_MIN	= uint8(0);
		constexpr auto UINT16_MIN	= uint16(0);
		constexpr auto UINT32_MIN	= uint32(0);
		constexpr auto UINT64_MIN	= uint64(0);
		constexpr auto UINT8_MAX	= uint8(0xff);
		constexpr auto UINT16_MAX	= uint16(0xffff);
		constexpr auto UINT32_MAX	= uint32(0xffffffff);
		constexpr auto UINT64_MAX	= uint64(0xffffffffffffffff);
		constexpr auto REAL_INF		= real(1e+38);
		constexpr auto REAL_PI		= real(3.1415926535);
		constexpr auto REAL_2_PI	= real(6.28318530718);
		constexpr auto REAL_EPSILON = real(1.192092896e-06); 
		constexpr auto REAL_D2R_FRAC= real(0.01745329251);
		constexpr auto REAL_R2D_FRAC= real(57.2957795131);
	}


}
