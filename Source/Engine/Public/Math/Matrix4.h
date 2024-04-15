#pragma once

#include <Math/Matrix3.h>

namespace Neowise {
    /**
    *
    */
    struct NW_API FMatrix4 {
        ~FMatrix4() = default;

        constexpr FMatrix4() = default;
        explicit FMatrix4(TReal v);
        FMatrix4(
            TReal x0, TReal y0, TReal z0, TReal  w0,
            TReal x1, TReal y1, TReal z1, TReal  w1,
            TReal x2, TReal y2, TReal z2, TReal  w2,
            TReal x3, TReal y3, TReal z3, TReal  w3
        );
        FMatrix4(
            const FVector4& col0,
            const FVector4& col1,
            const FVector4& col2,
            const FVector4& col3
        );

        FMatrix4(const FMatrix4&) = default;
        FMatrix4(FMatrix4&&) = default;
        FMatrix4& operator=(const FMatrix4&) = default;
        FMatrix4& operator=(FMatrix4&&) = default;

        bool operator==(const FMatrix4& r) const;
        bool operator!=(const FMatrix4& r) const;

        FMatrix4& operator+=(const FMatrix4& r);
        FMatrix4& operator+=(const FMatrix3& r);
        FMatrix4& operator+=(const FVector4& r);
        FMatrix4& operator+=(const FVector3& r);
        FMatrix4& operator+=(const FVector2& r);
        FMatrix4& operator+=(TReal r);
        FMatrix4& operator-=(const FMatrix4& r);
        FMatrix4& operator-=(const FMatrix3& r);
        FMatrix4& operator-=(const FVector4& r);
        FMatrix4& operator-=(const FVector3& r);
        FMatrix4& operator-=(const FVector2& r);
        FMatrix4& operator-=(TReal r);
        FMatrix4& operator*=(const FMatrix4& r);
        FMatrix4& operator*=(const FMatrix3& r);
        FMatrix4& operator*=(const FVector4& r);
        FMatrix4& operator*=(const FVector3& r);
        FMatrix4& operator*=(const FVector2& r);
        FMatrix4& operator*=(TReal r);
        FMatrix4& operator/=(const FMatrix4& r);
        FMatrix4& operator/=(const FMatrix3& r);
        FMatrix4& operator/=(const FVector4& r);
        FMatrix4& operator/=(const FVector3& r);
        FMatrix4& operator/=(const FVector2& r);
        FMatrix4& operator/=(TReal r);

        FMatrix4 operator-() const;

        operator FQuaternion() const;

        FMatrix4 operator+(TReal r) const;
        FMatrix4 operator+(const FVector2& r) const;
        FMatrix4 operator+(const FVector3& r) const;
        FMatrix4 operator+(const FVector4& r) const;
        FMatrix4 operator+(const FMatrix3& r) const;
        FMatrix4 operator+(const FMatrix4& r) const;
        FMatrix4 operator-(TReal r) const;
        FMatrix4 operator-(const FVector2& r) const;
        FMatrix4 operator-(const FVector3& r) const;
        FMatrix4 operator-(const FVector4& r) const;
        FMatrix4 operator-(const FMatrix3& r) const;
        FMatrix4 operator-(const FMatrix4& r) const;
        FMatrix4 operator*(TReal r) const;
        FVector2 operator*(const FVector2& r) const;
        FVector3 operator*(const FVector3& r) const;
        FVector4 operator*(const FVector4& r) const;
        FMatrix3 operator*(const FMatrix3& r) const;
        FMatrix4 operator*(const FMatrix4& r) const;
        FMatrix4 operator/(TReal r) const;
        FVector2 operator / (const FVector2 & r) const;
        FVector3 operator / (const FVector3 & r) const;
        FVector4 operator/(const FVector4& r) const;
        FMatrix3 operator/(const FMatrix3& r) const;
        FMatrix4 operator/(const FMatrix4& r) const;

        FVector4& operator[](TInt32 i);
        FVector4 operator[](TInt32 i) const;

        FVector4 columns[4] = {};
    };

    FMatrix4 operator+(TReal a, const FMatrix4& b);
    FMatrix4 operator-(TReal a, const FMatrix4& b);
    FMatrix4 operator*(TReal a, const FMatrix4& b);
    FVector4 operator*(const FVector4& a, const FMatrix4& b);
    FMatrix4 operator/(TReal a, const FMatrix4& b);
    FVector4 operator/(const FVector4& a, const FMatrix4& b);

    using FMat4 = FMatrix4;


}
