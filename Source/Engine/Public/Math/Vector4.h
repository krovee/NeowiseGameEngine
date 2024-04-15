#pragma once

#include <Math/Vector3.h>

namespace Neowise {
    /** 
    * 
    */
    struct NW_API FVector4 {

        ~FVector4() = default;

        FVector4() : _data() {}
        explicit FVector4(TReal o);
        FVector4(TReal x, TReal y, TReal z, TReal w);
        FVector4(const FVector3& xyz, TReal w);
        FVector4(TReal x, const FVector3& yzw);
        FVector4(const FVector2& xy, const FVector2& zw);

        FVector4(const FVector4&);
        FVector4(FVector4&&);
        FVector4& operator=(const FVector4&);
        FVector4& operator=(FVector4&&);

        bool operator==(const FVector4&) const;
        bool operator!=(const FVector4&) const;
        bool operator<(const FVector4&) const;
        bool operator<=(const FVector4&) const;
        bool operator>(const FVector4&) const;
        bool operator>=(const FVector4&) const;

        FVector4& operator+=(const FVector4&);
        FVector4& operator+=(const FVector3&);
        FVector4& operator+=(const FVector2&);
        FVector4& operator+=(TReal);
        FVector4& operator-=(const FVector4&);
        FVector4& operator-=(const FVector3&);
        FVector4& operator-=(const FVector2&);
        FVector4& operator-=(TReal);
        FVector4& operator*=(const FVector4&);
        FVector4& operator*=(const FVector3&);
        FVector4& operator*=(const FVector2&);
        FVector4& operator*=(TReal);
        FVector4& operator/=(const FVector4&);
        FVector4& operator/=(const FVector3&);
        FVector4& operator/=(const FVector2&);
        FVector4& operator/=(TReal);

        FVector4 operator-() const;

        operator FVector3() const;
        operator FVector2() const;

        FVector4 operator+(const FVector4&) const;
        FVector4 operator+(const FVector3&) const;
        FVector4 operator+(const FVector2&) const;
        FVector4 operator+(TReal) const;
        FVector4 operator-(const FVector4&) const;
        FVector4 operator-(const FVector3&) const;
        FVector4 operator-(const FVector2&) const;
        FVector4 operator-(TReal) const;
        FVector4 operator*(const FVector4&) const;
        FVector4 operator*(const FVector3&) const;
        FVector4 operator*(const FVector2&) const;
        FVector4 operator*(TReal) const;
        FVector4 operator/(const FVector4&) const;
        FVector4 operator/(const FVector3&) const;
        FVector4 operator/(const FVector2&) const;
        FVector4 operator/(TReal) const;

        TReal& operator[](TInt32 i);
        TReal operator[](TInt32 i) const;

        static const FVector4 zero;
        static const FVector4 one;
        static const FVector4 up;
        static const FVector4 left;
        static const FVector4 down;
        static const FVector4 right;
        static const FVector4 forward;
        static const FVector4 back;

        union {
            __m128 _mm = {};
            TReal _data[4];
            FVector3 rgb;
            FVector3 xyz;
            FVector2 xy;
            struct {
                TReal x;
                union {
                    struct {
                        TReal y;
                        union {
                            struct {
                                TReal z;
                                TReal w;
                            };
                        };
                    };
                };
            };
            struct {
                TReal r, g, b, a;
            };
        };

    };

    NW_API FVector4 operator+(const TReal a, const FVector4& b);
    NW_API FVector4 operator-(const TReal a, const FVector4& b);
    NW_API FVector4 operator*(const TReal a, const FVector4& b);
    NW_API FVector4 operator/(const TReal a, const FVector4& b);

    using FVec4 = FVector4;

}
