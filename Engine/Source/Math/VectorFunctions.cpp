#include <Math/Math.h>

namespace Neowise {

	static FVector2 recallfn(const FVector2& v, real(*fn)(real)) {
		return {
			fn(v[0]),
			fn(v[1])
		};
	}
	static FVector2 recallfn(const FVector2& v1, const FVector2& v2, real(*fn)(real, real)) {
		return {
			fn(v1[0], v2[0]),
			fn(v1[1], v2[1])
		};
	}
	static FVector3 recallfn(const FVector3& v, real(*fn)(real)) {
		return {
			fn(v[0]),
			fn(v[1]),
			fn(v[2])
		};
	}
	static FVector3 recallfn(const FVector3& v1, const FVector3& v2, real(*fn)(real, real)) {
		return {
			fn(v1[0], v2[0]),
			fn(v1[1], v2[1]),
			fn(v1[2], v2[2])
		};
	}
	static FVector4 recallfn(const FVector4& v, real(*fn)(real)) {
		return {
			fn(v[0]),
			fn(v[1]),
			fn(v[2]),
			fn(v[3])
		};
	}
	static FVector4 recallfn(const FVector4& v1, const FVector4& v2, real(*fn)(real, real)) {
		return {
			fn(v1[0], v2[0]),
			fn(v1[1], v2[1]),
			fn(v1[2], v2[2]),
			fn(v1[3], v2[3])
		};
	}

	FVector2 Neowise::sin(const FVector2& v) {
		return recallfn(v, sin);
	}

	FVector2 cos(const FVector2& v) {
		return recallfn(v, cos);
	}

	FVector2 tan(const FVector2& v) {
		return recallfn(v, tan);
	}

	FVector2 asin(const FVector2& v) {
		return recallfn(v, asin);
	}

	FVector2 acos(const FVector2& v) {
		return recallfn(v, acos);
	}

	FVector2 atan(const FVector2& v) {
		return recallfn(v, atan);
	}

	FVector2 dot(const FVector2& x, const FVector2& y) {
		return recallfn(x, y, dot);
	}

	FVector2 atan2(const FVector2& y, const FVector2& x) {
		return recallfn(y, x, atan2);
	}

	FVector2 sinh(const FVector2& v) {
		return recallfn(v, sinh);
	}

	FVector2 cosh(const FVector2& v) {
		return recallfn(v, cosh);
	}

	FVector2 tanh(const FVector2& v) {
		return recallfn(v, tanh);
	}

	FVector2 asinh(const FVector2& v) {
		return recallfn(v, asinh);
	}

	FVector2 acosh(const FVector2& v) {
		return recallfn(v, acosh);
	}

	FVector2 atanh(const FVector2& v) {
		return recallfn(v, atanh);
	}

	FVector2 pow(const FVector2& base, const FVector2& exp) {
		return recallfn(base, exp, pow);
	}

	FVector2 sqrt(const FVector2& v) {
		return recallfn(v, sqrt);
	}

	FVector2 cbrt(const FVector2& v) {
		return recallfn(v, cbrt);
	}

	FVector2 hypot(const FVector2& x, const FVector2& y){
		return recallfn(x, y, hypot);
	}

	FVector2 rsqrt(const FVector2& v) {
		return recallfn(v, rsqrt);
	}

	FVector2 modf(const FVector2& arg, FVector2* iptr) {
		return {
			modf(arg[0], &(iptr->x)),
			modf(arg[1], &(iptr->y))
		};
	}

	FVector2 fabs(const FVector2& v) {
		return recallfn(v, fabs);
	}

	FVector2 fmod(const FVector2& x, const FVector2& y) {
		return recallfn(x, y, fmod);
	}

	FVector2 fma(const FVector2& x, const FVector2& y, const FVector2& z) {
		return {
			fma(x[0], y[0], z[0]),
			fma(x[1], y[1], z[1])
		};
	}

	FVector2 log(const FVector2& v) {
		return recallfn(v, log);
	}

	FVector2 log2(const FVector2& v){
		return recallfn(v, log2);
	}

	FVector2 log10(const FVector2& v) {
		return recallfn(v, log10);
	}

	FVector2 ceil(const FVector2& v) {
		return recallfn(v, ceil);
	}

	FVector2 floor(const FVector2& v) {
		return recallfn(v, floor);
	}

	FVector2 trunc(const FVector2& v) {
		return recallfn(v, trunc);
	}

	FVector2 round(const FVector2& v) {
		return recallfn(v, round);
	}

	FVector2 mix(const FVector2& x, const FVector2& y, real t) {
		return {
			mix(x[0], y[0], t),
			mix(x[1], y[1], t)
		};
	}

	
	FVector3 Neowise::sin(const FVector3& v) {
		return recallfn(v, sin);
	}

	FVector3 cos(const FVector3& v) {
		return recallfn(v, cos);
	}

	FVector3 tan(const FVector3& v) {
		return recallfn(v, tan);
	}

	FVector3 asin(const FVector3& v) {
		return recallfn(v, asin);
	}

	FVector3 acos(const FVector3& v) {
		return recallfn(v, acos);
	}

	FVector3 atan(const FVector3& v) {
		return recallfn(v, atan);
	}

	FVector3 dot(const FVector3& x, const FVector3& y) {
		return recallfn(x, y, dot);
	}

	FVector3 atan2(const FVector3& y, const FVector3& x) {
		return recallfn(y, x, atan2);
	}

	FVector3 sinh(const FVector3& v) {
		return recallfn(v, sinh);
	}

	FVector3 cosh(const FVector3& v) {
		return recallfn(v, cosh);
	}

	FVector3 tanh(const FVector3& v) {
		return recallfn(v, tanh);
	}

	FVector3 asinh(const FVector3& v) {
		return recallfn(v, asinh);
	}

	FVector3 acosh(const FVector3& v) {
		return recallfn(v, acosh);
	}

	FVector3 atanh(const FVector3& v) {
		return recallfn(v, atanh);
	}

	FVector3 pow(const FVector3& base, const FVector3& exp) {
		return recallfn(base, exp, pow);
	}

	FVector3 sqrt(const FVector3& v) {
		return recallfn(v, sqrt);
	}

	FVector3 cbrt(const FVector3& v) {
		return recallfn(v, cbrt);
	}

	FVector3 hypot(const FVector3& x, const FVector3& y){
		return recallfn(x, y, hypot);
	}

	FVector3 rsqrt(const FVector3& v) {
		return recallfn(v, rsqrt);
	}

	FVector3 modf(const FVector3& arg, FVector3* iptr) {
		return {
			modf(arg[0], &(iptr->x)),
			modf(arg[1], &(iptr->y)),
			modf(arg[1], &(iptr->z))
		};
	}

	FVector3 fabs(const FVector3& v) {
		return recallfn(v, fabs);
	}

	FVector3 fmod(const FVector3& x, const FVector3& y) {
		return recallfn(x, y, fmod);
	}

	FVector3 fma(const FVector3& x, const FVector3& y, const FVector3& z) {
		return {
			fma(x[0], y[0], z[0]),
			fma(x[1], y[1], z[1]),
			fma(x[2], y[2], z[2])
		};
	}

	FVector3 log(const FVector3& v) {
		return recallfn(v, log);
	}

	FVector3 log2(const FVector3& v){
		return recallfn(v, log2);
	}

	FVector3 log10(const FVector3& v) {
		return recallfn(v, log10);
	}

	FVector3 ceil(const FVector3& v) {
		return recallfn(v, ceil);
	}

	FVector3 floor(const FVector3& v) {
		return recallfn(v, floor);
	}

	FVector3 trunc(const FVector3& v) {
		return recallfn(v, trunc);
	}

	FVector3 round(const FVector3& v) {
		return recallfn(v, round);
	}

	FVector3 mix(const FVector3& x, const FVector3& y, real t) {
		return {
			mix(x[0], y[0], t),
			mix(x[1], y[1], t),
			mix(x[2], y[2], t)
		};
	}

	FVector3 cross(const FVector3& x, const FVector3& y) {
		return {
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y
		};
	}

	
	FVector4 Neowise::sin(const FVector4& v) {
		return recallfn(v, sin);
	}

	FVector4 cos(const FVector4& v) {
		return recallfn(v, cos);
	}

	FVector4 tan(const FVector4& v) {
		return recallfn(v, tan);
	}

	FVector4 asin(const FVector4& v) {
		return recallfn(v, asin);
	}

	FVector4 acos(const FVector4& v) {
		return recallfn(v, acos);
	}

	FVector4 atan(const FVector4& v) {
		return recallfn(v, atan);
	}

	FVector4 dot(const FVector4& x, const FVector4& y) {
		return recallfn(x, y, dot);
	}

	FVector4 atan2(const FVector4& y, const FVector4& x) {
		return recallfn(y, x, atan2);
	}

	FVector4 sinh(const FVector4& v) {
		return recallfn(v, sinh);
	}

	FVector4 cosh(const FVector4& v) {
		return recallfn(v, cosh);
	}

	FVector4 tanh(const FVector4& v) {
		return recallfn(v, tanh);
	}

	FVector4 asinh(const FVector4& v) {
		return recallfn(v, asinh);
	}

	FVector4 acosh(const FVector4& v) {
		return recallfn(v, acosh);
	}

	FVector4 atanh(const FVector4& v) {
		return recallfn(v, atanh);
	}

	FVector4 pow(const FVector4& base, const FVector4& exp) {
		return recallfn(base, exp, pow);
	}

	FVector4 sqrt(const FVector4& v) {
		return recallfn(v, sqrt);
	}

	FVector4 cbrt(const FVector4& v) {
		return recallfn(v, cbrt);
	}

	FVector4 hypot(const FVector4& x, const FVector4& y){
		return recallfn(x, y, hypot);
	}

	FVector4 rsqrt(const FVector4& v) {
		return recallfn(v, rsqrt);
	}

	FVector4 modf(const FVector4& arg, FVector4* iptr) {
		return {
			modf(arg[0], &(iptr->x)),
			modf(arg[1], &(iptr->y)),
			modf(arg[2], &(iptr->z)),
			modf(arg[3], &(iptr->w)),
		};
	}

	FVector4 fabs(const FVector4& v) {
		return recallfn(v, fabs);
	}

	FVector4 fmod(const FVector4& x, const FVector4& y) {
		return recallfn(x, y, fmod);
	}

	FVector4 fma(const FVector4& x, const FVector4& y, const FVector4& z) {
		return {
			fma(x[0], y[0], z[0]),
			fma(x[1], y[1], z[1]),
			fma(x[2], y[2], z[2]),
			fma(x[3], y[3], z[3])
		};
	}

	FVector4 log(const FVector4& v) {
		return recallfn(v, log);
	}

	FVector4 log2(const FVector4& v){
		return recallfn(v, log2);
	}

	FVector4 log10(const FVector4& v) {
		return recallfn(v, log10);
	}

	FVector4 ceil(const FVector4& v) {
		return recallfn(v, ceil);
	}

	FVector4 floor(const FVector4& v) {
		return recallfn(v, floor);
	}

	FVector4 trunc(const FVector4& v) {
		return recallfn(v, trunc);
	}

	FVector4 round(const FVector4& v) {
		return recallfn(v, round);
	}

	FVector4 mix(const FVector4& x, const FVector4& y, real t) {
		return {
			mix(x[0], y[0], t),
			mix(x[1], y[1], t),
			mix(x[2], y[2], t),
			mix(x[3], y[3], t)
		};
	}

}
