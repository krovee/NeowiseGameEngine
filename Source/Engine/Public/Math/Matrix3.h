#pragma once

#include <Math/Quaternion.h>

namespace Neowise {
    struct FMatrix4;

    /** 
    * 
    */
    struct NW_API FMatrix3 {
        ~FMatrix3() = default;

        constexpr FMatrix3() = default;
        explicit FMatrix3(TReal v);
        FMatrix3(
            TReal x0, TReal y0, TReal z0,
            TReal x1, TReal y1, TReal z1,
            TReal x2, TReal y2, TReal z2
        );
        FMatrix3(
            const FVector3& col0,
            const FVector3& col1,
            const FVector3& col2
        );
        explicit FMatrix3(const FMatrix4& m);

        FMatrix3(const FMatrix3&) = default;
        FMatrix3(FMatrix3&&) = default;
        FMatrix3& operator=(const FMatrix3&) = default;
        FMatrix3& operator=(FMatrix3&&) = default;

        bool operator==(const FMatrix3& r) const;
        bool operator!=(const FMatrix3& r) const;

        FMatrix3& operator+=(const FMatrix3& r);
        FMatrix3& operator+=(const FVector4& r);
        FMatrix3& operator+=(const FVector3& r);
        FMatrix3& operator+=(const FVector2& r);
        FMatrix3& operator+=(TReal r);
        FMatrix3& operator-=(const FMatrix3& r);
        FMatrix3& operator-=(const FVector4& r);
        FMatrix3& operator-=(const FVector3& r);
        FMatrix3& operator-=(const FVector2& r);
        FMatrix3& operator-=(TReal r);
        FMatrix3& operator*=(const FMatrix3& r);
        FMatrix3& operator*=(const FVector4& r);
        FMatrix3& operator*=(const FVector3& r);
        FMatrix3& operator*=(const FVector2& r);
        FMatrix3& operator*=(TReal r);
        FMatrix3& operator/=(const FMatrix3& r);
        FMatrix3& operator/=(const FVector4& r);
        FMatrix3& operator/=(const FVector3& r);
        FMatrix3& operator/=(const FVector2& r);
        FMatrix3& operator/=(TReal r);

        FMatrix3 operator-() const;

        operator FQuaternion() const;

        FMatrix3 operator+(TReal r) const;
        FMatrix3 operator+(const FMatrix3& r) const;
        FMatrix3 operator-(TReal r) const;
        FMatrix3 operator-(const FMatrix3& r) const;
        FMatrix3 operator*(TReal r) const;
        FMatrix3 operator*(const FMatrix3& r) const;
        FVector3 operator*(const FVector3& r) const;
        FMatrix3 operator/(TReal r) const;
        FMatrix3 operator/(const FMatrix3& r) const;
        FVector3 operator/(const FVector3& r) const;

        FVector3& operator[](TInt32 i);
        FVector3 operator[](TInt32 i) const;

        FVector3 columns[3] = {};
    };

    FMatrix3 operator+(TReal a, const FMatrix3& b);
    FMatrix3 operator-(TReal a, const FMatrix3& b);
    FMatrix3 operator*(TReal a, const FMatrix3& b);
    FVector3 operator*(const FVector3& a, const FMatrix3& b);
    FMatrix3 operator/(TReal a, const FMatrix3& b);
    FVector3 operator/(const FVector3& a, const FMatrix3& b);


    using FMat3 = FMatrix3;


}
