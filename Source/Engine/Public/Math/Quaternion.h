#pragma once

#include <Math/Vector4.h>

namespace Neowise {
    struct FMatrix4;

    /** 
    * 
    */
    struct NW_API FQuaternion {
        ~FQuaternion() = default;

        constexpr FQuaternion() : _data() {}
        FQuaternion(TReal x, TReal y, TReal z, TReal w);
        explicit FQuaternion(const FVector3& eulerAngles);
        explicit FQuaternion(const FVector3& axis, const TReal angle);
        FQuaternion(const FVector3& normalized1, const FVector3& normalized2);

        FQuaternion(const FQuaternion&) = default;
        FQuaternion(FQuaternion&&) = default;
        FQuaternion& operator=(const FQuaternion&) = default;
        FQuaternion& operator=(FQuaternion&&) = default;

        TBool operator==(const FQuaternion&) const;
        TBool operator!=(const FQuaternion&) const;

        FQuaternion& operator+=(const FQuaternion&);
        FQuaternion& operator-=(const FQuaternion&);
        FQuaternion& operator*=(const FQuaternion&);
        FQuaternion& operator*=(TReal);
        FQuaternion& operator/=(TReal);

        FQuaternion operator-() const;

        // operator FMatrix3() const;
        // operator FMatrix4() const;

        FQuaternion operator+(const FQuaternion&) const;
        FQuaternion operator-(const FQuaternion&) const;
        FQuaternion operator*(const FQuaternion&) const;
        FVector3 operator*(const FVector3&) const;
        FVector4 operator*(const FVector4&) const;
        FQuaternion operator*(TReal) const;
        FQuaternion operator/(TReal) const;

        TReal angle() const;
        TReal roll() const;
        TReal pitch() const;
        TReal yaw() const;

        FVector3 axis() const;
        FVector3 euler() const;

        void apply(FMatrix4& m);

        union {
            TReal _data[4] = {};
            struct {
                TReal x, y, z, w;
            };
        };

    };

    FVector3 operator*(const FVector3&, const FQuaternion&);
    FVector4 operator*(const FVector4&, const FQuaternion&);
    FQuaternion operator*(TReal, const FQuaternion&);

}
