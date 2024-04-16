#pragma once

#include <Math/Vector2.h>

namespace Neowise {
    /**
    * Linear algebra math vector3 representation structure.
    */
    struct NW_API FVector3 {

        ~FVector3() = default;

        constexpr FVector3() : _data() {}
        explicit FVector3(TReal v);
        FVector3(TReal x, TReal y, TReal z);
        FVector3(const FVector2& xy, TReal z);
        FVector3(TReal x, const FVector2& yz);

        FVector3(const FVector3&);
        FVector3(FVector3&&);
        FVector3& operator=(const FVector3&);
        FVector3& operator=(FVector3&&); 

        TBool operator==(const FVector3&) const;
        TBool operator!=(const FVector3&) const;
        TBool operator<(const FVector3&) const;
        TBool operator<=(const FVector3&) const;
        TBool operator>(const FVector3&) const;
        TBool operator>=(const FVector3&) const;

        FVector3& operator+=(const FVector3&);
        FVector3& operator+=(const FVector2&);
        FVector3& operator+=(TReal);
        FVector3& operator-=(const FVector3&);
        FVector3& operator-=(const FVector2&);
        FVector3& operator-=(TReal);
        FVector3& operator*=(const FVector3&);
        FVector3& operator*=(const FVector2&);
        FVector3& operator*=(TReal);
        FVector3& operator/=(const FVector3&);
        FVector3& operator/=(const FVector2&);
        FVector3& operator/=(TReal);

        FVector3 operator-() const;

        operator FVector2() const;

        FVector3 operator+(const FVector3&) const;
        FVector3 operator+(const FVector2&) const;
        FVector3 operator+(TReal) const;
        FVector3 operator-(const FVector3&) const;
        FVector3 operator-(const FVector2&) const;
        FVector3 operator-(TReal) const;
        FVector3 operator*(const FVector3&) const;
        FVector3 operator*(const FVector2&) const;
        FVector3 operator*(TReal) const;
        FVector3 operator/(const FVector3&) const;
        FVector3 operator/(const FVector2&) const;
        FVector3 operator/(TReal) const;

        TReal& operator[](TInt32 i);
        TReal  operator[](TInt32 i) const;

        static const FVector3 zero;
        static const FVector3 one;
        static const FVector3 up;
        static const FVector3 left;
        static const FVector3 down;
        static const FVector3 right;
        static const FVector3 forward;
        static const FVector3 back;

        union {
            TReal _data[3] = {};
            struct { TReal x, y, z; };
            struct { TReal r, g, b; };
            FVector2 xy;
            FVector2 rg;
            FVector2 uv;
        };
    };

    NW_API FVector3 operator+(const TReal a, const FVector3& b);
    NW_API FVector3 operator-(const TReal a, const FVector3& b);
    NW_API FVector3 operator*(const TReal a, const FVector3& b);
    NW_API FVector3 operator/(const TReal a, const FVector3& b);

    using FVec3 = FVector3;
}
