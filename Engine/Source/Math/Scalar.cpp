#include <Math/Scalar.h>

#include <cmath>
#include <Base/Templated.h>

namespace Neowise {
	real sin(real x) {
		return std::sin(x);
	}
	
	real dot(real x, real y) {
		return x * y;
	}
	
	real cos(real x) {
		return std::cos(x);
	}
	
	real tan(real x) {
		return std::tan(x);
	}
	
	real asin(real x) {
		return std::asin(x);
	}
	
	real acos(real x) {
		return std::acos(x);
	}
	
	real atan(real x) {
		return std::atan(x);
	}
	
	real atan2(real y, real x) {
		return std::atan2(y, x);
	}
	
	real sinh(real x) {
		return std::sinh(x);
	}
	
	real cosh(real x) {
		return std::cosh(x);
	}
	
	real tanh(real x) {
		return std::tanh(x);
	}
	
	real asinh(real x) {
		return std::asinh(x);
	}
	
	real acosh(real x) {
		return std::acosh(x);
	}
	
	real atanh(real x) {
		return std::atanh(x);
	}
	
	real pow(real base, real exp) {
		return std::pow(base, exp);
	}
	
	real sqrt(real x) {
		return std::sqrt(x);
	}
	
	real cbrt(real x) {
		return std::cbrt(x);
	}
	
	real hypot(real x, real y) {
		return std::hypot(x, y);
	}
	
	real rsqrt(real x) {
		union {
			real f;
			TFloatAsIntRep i;
		} conv  = { .f = x };
		conv.i  = floatPointEvilHack - (conv.i >> 1);
		conv.f *= real(1.5) - (x * real(0.5) * conv.f * conv.f);
		return conv.f;
	}
	
	real modf(real arg, real* iptr) {
		return std::modf(arg, iptr);
	}
	
	real fabs(real x) {
		return std::fabs(x);
	}
	
	real fmod(real x, real y) {
		return std::fmod(x, y);
	}
	
	real fma(real x, real y, real z) {
		return std::fma(x, y, z);
	}
	
	real log(real x) {
		return std::log(x);
	}
	
	real log2(real x) {
		return std::log2(x);
	}
	
	real log10(real x) {
		return std::log10(x);
	}
	
	real ceil(real x) {
		return std::ceil(x);
	}
	
	real floor(real x) {
		return std::floor(x);
	}
	
	real trunc(real x) {
		return std::trunc(x);
	}
	
	real round(real x) {
		return std::round(x);
	}
	
	real mix(real x, real y, real t) {
		return x * (1 - t) + y * t;
	}
}
