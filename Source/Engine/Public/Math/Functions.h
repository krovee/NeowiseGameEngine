#pragma once

#include <Math/Scalar.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Matrix3.h>
#include <Math/Matrix4.h>
#include <Math/Quaternion.h>

namespace Neowise {

	NW_API FVector2 sin(const FVector2& v);
	NW_API FVector2 cos(const FVector2& v);
	NW_API FVector2 tan(const FVector2& v);
	NW_API FVector2 asin(const FVector2& v);
	NW_API FVector2 acos(const FVector2& v);
	NW_API FVector2 atan(const FVector2& v);
	NW_API real 	dot(const FVector2& x, const FVector2& y);
	NW_API FVector2 atan2(const FVector2& y, const FVector2& x);
	NW_API FVector2 sinh(const FVector2& v);
	NW_API FVector2 cosh(const FVector2& v);
	NW_API FVector2 tanh(const FVector2& v);
	NW_API FVector2 asinh(const FVector2& v);
	NW_API FVector2 acosh(const FVector2& v);
	NW_API FVector2 atanh(const FVector2& v);
	NW_API FVector2 pow(const FVector2& base, const FVector2& exp);
	NW_API FVector2 sqrt(const FVector2& v);
	NW_API FVector2 cbrt(const FVector2& v);
	NW_API FVector2 hypot(const FVector2& x, const FVector2& y);
	NW_API FVector2 rsqrt(const FVector2& v);
	NW_API FVector2 modf(const FVector2& arg, FVector2* iptr);
	NW_API FVector2 fabs(const FVector2& v);
	NW_API FVector2 fmod(const FVector2& x, const FVector2& y);
	NW_API FVector2 fma(const FVector2& x, const FVector2& y, const FVector2& z);
	NW_API FVector2 log(const FVector2& v);
	NW_API FVector2 log2(const FVector2& v);
	NW_API FVector2 log10(const FVector2& v);
	NW_API FVector2 ceil(const FVector2& v);
	NW_API FVector2 floor(const FVector2& v);
	NW_API FVector2 trunc(const FVector2& v);
	NW_API FVector2 round(const FVector2& v);
	NW_API FVector2 mix(const FVector2& x, const FVector2& y, real t);

	NW_API FVector3 sin(const FVector3& v);
	NW_API FVector3 cos(const FVector3& v);
	NW_API FVector3 tan(const FVector3& v);
	NW_API FVector3 asin(const FVector3& v);
	NW_API FVector3 acos(const FVector3& v);
	NW_API FVector3 atan(const FVector3& v);
	NW_API real 	dot(const FVector3& x, const FVector3& y);
	NW_API FVector3 atan2(const FVector3& y, const FVector3& x);
	NW_API FVector3 sinh(const FVector3& v);
	NW_API FVector3 cosh(const FVector3& v);
	NW_API FVector3 tanh(const FVector3& v);
	NW_API FVector3 asinh(const FVector3& v);
	NW_API FVector3 acosh(const FVector3& v);
	NW_API FVector3 atanh(const FVector3& v);
	NW_API FVector3 pow(const FVector3& base, const FVector3& exp);
	NW_API FVector3 sqrt(const FVector3& v);
	NW_API FVector3 cbrt(const FVector3& v);
	NW_API FVector3 hypot(const FVector3& x, const FVector3& y);
	NW_API FVector3 rsqrt(const FVector3& v);
	NW_API FVector3 modf(const FVector3& arg, FVector3* iptr);
	NW_API FVector3 fabs(const FVector3& v);
	NW_API FVector3 fmod(const FVector3& x, const FVector3& y);
	NW_API FVector3 fma(const FVector3& x, const FVector3& y, const FVector3& z);
	NW_API FVector3 log(const FVector3& v);
	NW_API FVector3 log2(const FVector3& v);
	NW_API FVector3 log10(const FVector3& v);
	NW_API FVector3 ceil(const FVector3& v);
	NW_API FVector3 floor(const FVector3& v);
	NW_API FVector3 trunc(const FVector3& v);
	NW_API FVector3 round(const FVector3& v);
	NW_API FVector3 mix(const FVector3& x, const FVector3& y, real t);
	NW_API FVector3 cross(const FVector3& x, const FVector3& y);

	NW_API FVector4 sin(const FVector4& v);
	NW_API FVector4 cos(const FVector4& v);
	NW_API FVector4 tan(const FVector4& v);
	NW_API FVector4 asin(const FVector4& v);
	NW_API FVector4 acos(const FVector4& v);
	NW_API FVector4 atan(const FVector4& v);
	NW_API real 	dot(const FVector4& x, const FVector4& y);
	NW_API FVector4 atan2(const FVector4& y, const FVector4& x);
	NW_API FVector4 sinh(const FVector4& v);
	NW_API FVector4 cosh(const FVector4& v);
	NW_API FVector4 tanh(const FVector4& v);
	NW_API FVector4 asinh(const FVector4& v);
	NW_API FVector4 acosh(const FVector4& v);
	NW_API FVector4 atanh(const FVector4& v);
	NW_API FVector4 pow(const FVector4& base, const FVector4& exp);
	NW_API FVector4 sqrt(const FVector4& v);
	NW_API FVector4 cbrt(const FVector4& v);
	NW_API FVector4 hypot(const FVector4& x, const FVector4& y);
	NW_API FVector4 rsqrt(const FVector4& v);
	NW_API FVector4 modf(const FVector4& arg, FVector4* iptr);
	NW_API FVector4 fabs(const FVector4& v);
	NW_API FVector4 fmod(const FVector4& x, const FVector4& y);
	NW_API FVector4 fma(const FVector4& x, const FVector4& y, const FVector4& z);
	NW_API FVector4 log(const FVector4& v);
	NW_API FVector4 log2(const FVector4& v);
	NW_API FVector4 log10(const FVector4& v);
	NW_API FVector4 ceil(const FVector4& v);
	NW_API FVector4 floor(const FVector4& v);
	NW_API FVector4 trunc(const FVector4& v);
	NW_API FVector4 round(const FVector4& v);
	NW_API FVector4 mix(const FVector4& x, const FVector4& y, real t);

	NW_API FVector2 normalize(const FVector2& v);
	NW_API FVector3 normalize(const FVector3& v);
	NW_API FVector4 normalize(const FVector4& v);

	NW_API FMatrix3 inverse(const FMatrix3& m);
	NW_API FMatrix3 transpose(const FMatrix3& m);
	NW_API FMatrix4 inverse(const FMatrix4& m);
	NW_API FMatrix4 transpose(const FMatrix4& m);
	NW_API FMatrix4 translate(const FMatrix4& m, const FVector3& translation);
	NW_API FMatrix4 rotateAxis(const FMatrix4& m, const FVector3& axis, const real angle);
	NW_API FMatrix4 scale(const FMatrix4& m, const FVector3& s);
	NW_API FMatrix4 lookat(const FVector3& eye, const FVector3& center, const FVector3& up = FVector3::up);

}
