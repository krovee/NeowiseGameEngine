#include <Math/Scalar.h>

#include <cmath>
#include <Base/Templated.h>

namespace Neowise {
    TReal sin(TReal x) {
        return std::sin(x);
    }
    
    TReal dot(TReal x, TReal y) {
        return x * y;
    }
    
    TReal cos(TReal x) {
        return std::cos(x);
    }
    
    TReal tan(TReal x) {
        return std::tan(x);
    }
    
    TReal asin(TReal x) {
        return std::asin(x);
    }
    
    TReal acos(TReal x) {
        return std::acos(x);
    }
    
    TReal atan(TReal x) {
        return std::atan(x);
    }
    
    TReal atan2(TReal y, TReal x) {
        return std::atan2(y, x);
    }
    
    TReal sinh(TReal x) {
        return std::sinh(x);
    }
    
    TReal cosh(TReal x) {
        return std::cosh(x);
    }
    
    TReal tanh(TReal x) {
        return std::tanh(x);
    }
    
    TReal asinh(TReal x) {
        return std::asinh(x);
    }
    
    TReal acosh(TReal x) {
        return std::acosh(x);
    }
    
    TReal atanh(TReal x) {
        return std::atanh(x);
    }
    
    TReal pow(TReal base, TReal exp) {
        return std::pow(base, exp);
    }
    
    TReal sqrt(TReal x) {
        return std::sqrt(x);
    }
    
    TReal cbrt(TReal x) {
        return std::cbrt(x);
    }
    
    TReal hypot(TReal x, TReal y) {
        return std::hypot(x, y);
    }
    
    TReal rsqrt(TReal x) {
        union {
            TReal f;
            TFloatAsIntRep i;
        } conv  = { .f = x };
        conv.i  = kFpEvilHackValue - (conv.i >> 1);
        conv.f *= TReal(1.5) - (x * TReal(0.5) * conv.f * conv.f);
        return conv.f;
    }
    
    TReal modf(TReal arg, TReal* iptr) {
        return std::modf(arg, iptr);
    }
    
    TReal fabs(TReal x) {
        return std::fabs(x);
    }
    
    TReal fmod(TReal x, TReal y) {
        return std::fmod(x, y);
    }
    
    TReal fma(TReal x, TReal y, TReal z) {
        return std::fma(x, y, z);
    }
    
    TReal log(TReal x) {
        return std::log(x);
    }
    
    TReal log2(TReal x) {
        return std::log2(x);
    }
    
    TReal log10(TReal x) {
        return std::log10(x);
    }
    
    TReal ceil(TReal x) {
        return std::ceil(x);
    }
    
    TReal floor(TReal x) {
        return std::floor(x);
    }
    
    TReal trunc(TReal x) {
        return std::trunc(x);
    }
    
    TReal round(TReal x) {
        return std::round(x);
    }
    
    TReal mix(TReal x, TReal y, TReal t) {
        return x * (1 - t) + y * t;
    }
}
