#pragma once

#include <Math/Scalar.h>

namespace Neowise {
    /** 
    * Linear algebra math vector2 representation structure.
    */
    struct NW_API FVector2 {

        ~FVector2() = default;

        constexpr FVector2() : _data() {}
        explicit FVector2(TReal v);
        FVector2(TReal x, TReal y);

        FVector2(const FVector2&);
        FVector2(FVector2&&);
        FVector2& operator=(const FVector2&);
        FVector2& operator=(FVector2&&);

        bool operator==(const FVector2&) const;
        bool operator!=(const FVector2&) const;
        bool operator<(const FVector2&) const;
        bool operator<=(const FVector2&) const;
        bool operator>(const FVector2&) const;
        bool operator>=(const FVector2&) const;

        FVector2& operator+=(const FVector2&);
        FVector2& operator+=(TReal);
        FVector2& operator-=(const FVector2&);
        FVector2& operator-=(TReal);
        FVector2& operator*=(const FVector2&);
        FVector2& operator*=(TReal);
        FVector2& operator/=(const FVector2&);
        FVector2& operator/=(TReal);

        FVector2 operator-() const;

        FVector2 operator+(const FVector2&) const;
        FVector2 operator+(TReal) const;
        FVector2 operator-(const FVector2&) const;
        FVector2 operator-(TReal) const;
        FVector2 operator*(const FVector2&) const;
        FVector2 operator*(TReal) const;
        FVector2 operator/(const FVector2&) const;
        FVector2 operator/(TReal) const;

        TReal& operator[](TInt32 i);
        TReal  operator[](TInt32 i) const;

        static const FVector2 zero;
        static const FVector2 one;
        static const FVector2 left;
        static const FVector2 right;

        union {
            TReal _data[2] = {};
            struct { TReal x, y; };
            struct { TReal u, v; };
            struct { TReal r, g; };
        };
    };

    NW_API FVector2 operator+(const TReal a, const FVector2& b);
    NW_API FVector2 operator-(const TReal a, const FVector2& b);
    NW_API FVector2 operator*(const TReal a, const FVector2& b);
    NW_API FVector2 operator/(const TReal a, const FVector2& b);

    using FVec2 = FVector2;
}
