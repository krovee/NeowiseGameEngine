#include <Math/Math.h>

namespace Neowise {

    FMatrix3::FMatrix3(TReal v)
        : columns{
            FVector3(v, 0, 0),
            FVector3(0, v, 0),
            FVector3(0, 0, v)
        }
    {
    }

    FMatrix3::FMatrix3(TReal x0, TReal y0, TReal z0, TReal x1, TReal y1, TReal z1, TReal x2, TReal y2, TReal z2) 
        : columns{
            { x0, y0, z0 },
            { x1, y1, z1 },
            { x2, y2, z2 }
        }
    {
    }

    FMatrix3::FMatrix3(const FVector3& col0, const FVector3& col1, const FVector3& col2) 
        : columns{
            col0,
            col1,
            col2
        }
    {
    }

    FMatrix3::FMatrix3(const FMatrix4& m) 
        : columns{
            m[0].xyz,
            m[1].xyz,
            m[2].xyz
        }
    {
    }

    bool FMatrix3::operator==(const FMatrix3& r) const {
        return columns[0] == r[0] && columns[1] == r[1] && columns[2] == r[2];
    }

    bool FMatrix3::operator!=(const FMatrix3& r) const {
        return !(*this == r);
    }

    FMatrix3& FMatrix3::operator+=(const FMatrix3& r) {
        columns[0] += r[0];
        columns[1] += r[1];
        columns[2] += r[2];
        return *this;
    }

    FMatrix3& FMatrix3::operator+=(const FVector4& r) {
        columns[0] += r.xyz;
        columns[1] += r.xyz;
        columns[2] += r.xyz;
        return *this;
    }

    FMatrix3& FMatrix3::operator+=(const FVector3& r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        return *this;
    }

    FMatrix3& FMatrix3::operator+=(const FVector2& r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        return *this;
    }

    FMatrix3& FMatrix3::operator+=(TReal r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        return *this;
    }

    FMatrix3& FMatrix3::operator-=(const FMatrix3& r) {
        columns[0] -= r[0];
        columns[1] -= r[1];
        columns[2] -= r[2];
        return *this;
    }

    FMatrix3& FMatrix3::operator-=(const FVector4& r) {
        columns[0] -= r.xyz;
        columns[1] -= r.xyz;
        columns[2] -= r.xyz;
        return *this;
    }

    FMatrix3& FMatrix3::operator-=(const FVector3& r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator-=(const FVector2& r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator-=(TReal r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator*=(const FMatrix3& r) {
        return (*this = (*this * r));
    }

    FMatrix3& FMatrix3::operator*=(const FVector4& r) {
        columns[0] *= r.xyz;
        columns[1] *= r.xyz;
        columns[2] *= r.xyz;
        return *this;
    }

    FMatrix3& FMatrix3::operator*=(const FVector3& r) {
        columns[0] *= r;
        columns[1] *= r;
        columns[2] *= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator*=(const FVector2& r) {
        columns[0] *= r;
        columns[1] *= r;
        columns[2] *= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator*=(TReal r) {
        columns[0] *= r;
        columns[1] *= r;
        columns[2] *= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator/=(const FMatrix3& r) {
        columns[0] /= r[0];
        columns[1] /= r[1];
        columns[2] /= r[2];
        return *this;
    }

    FMatrix3& FMatrix3::operator/=(const FVector4& r) {
        columns[0] /= r.xyz;
        columns[1] /= r.xyz;
        columns[2] /= r.xyz;
        return *this;
    }

    FMatrix3& FMatrix3::operator/=(const FVector3& r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator/=(const FVector2& r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        return *this;
    }

    FMatrix3& FMatrix3::operator/=(TReal r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        return *this;
    }

    FMatrix3 FMatrix3::operator-() const {
        return {
            -columns[0],
            -columns[1],
            -columns[2]
        };
    }

    FMatrix3::operator FQuaternion() const {

        const auto fourXSquaredMinus1 = columns[0][0] - columns[1][1] - columns[2][2];
        const auto fourYSquaredMinus1 = columns[1][1] - columns[0][0] - columns[2][2];
        const auto fourZSquaredMinus1 = columns[2][2] - columns[0][0] - columns[1][1];
        const auto fourWSquaredMinus1 = columns[0][0] + columns[1][1] + columns[2][2];

        auto biggestIndex = 0;
        auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        const auto biggestVal = sqrt(fourBiggestSquaredMinus1 + (TReal)(1)) * (TReal)(0.5);
        const auto mult = (TReal)(0.25) / biggestVal;

        switch (biggestIndex)
        {
        case 0:
            return FQuaternion((columns[1][2] - columns[2][1]) * mult, (columns[2][0] - columns[0][2]) * mult, (columns[0][1] - columns[1][0]) * mult, biggestVal);
        case 1:
            return FQuaternion(biggestVal, (columns[0][1] + columns[1][0]) * mult, (columns[2][0] + columns[0][2]) * mult, (columns[1][2] - columns[2][1]) * mult);
        case 2:
            return FQuaternion((columns[0][1] + columns[1][0]) * mult, biggestVal, (columns[1][2] + columns[2][1]) * mult, (columns[2][0] - columns[0][2]) * mult);
        case 3:
            return FQuaternion((columns[2][0] + columns[0][2]) * mult, (columns[1][2] + columns[2][1]) * mult, biggestVal, (columns[0][1] - columns[1][0]) * mult);
        default:
            return FQuaternion(1, 0, 0, 0);
        }
    }

    FMatrix3 FMatrix3::operator+(TReal r) const {
        return FMatrix3(*this) += r;
    }

    FMatrix3 FMatrix3::operator+(const FMatrix3& r) const{
        return FMatrix3(*this) += r;
    }
    
    FMatrix3 FMatrix3::operator-(TReal r) const {
        return FMatrix3(*this) -= r;
    }

    FMatrix3 FMatrix3::operator-(const FMatrix3& r) const{
        return FMatrix3(*this) -= r;
    }

    FMatrix3 FMatrix3::operator*(TReal r) const {
        return FMatrix3(*this) *= r;
    }

    FMatrix3 FMatrix3::operator*(const FMatrix3& r) const {
        const auto a00 = columns[0][0];
        const auto a01 = columns[0][1];
        const auto a02 = columns[0][2];
        const auto a10 = columns[1][0];
        const auto a11 = columns[1][1];
        const auto a12 = columns[1][2];
        const auto a20 = columns[2][0];
        const auto a21 = columns[2][1];
        const auto a22 = columns[2][2];

        const auto b00 = r[0][0];
        const auto b01 = r[0][1];
        const auto b02 = r[0][2];
        const auto b10 = r[1][0];
        const auto b11 = r[1][1];
        const auto b12 = r[1][2];
        const auto b20 = r[2][0];
        const auto b21 = r[2][1];
        const auto b22 = r[2][2];

        FMatrix3 res;
        res[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
        res[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
        res[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
        res[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
        res[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
        res[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
        res[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
        res[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
        res[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
        return res;
    }

    FVector3 FMatrix3::operator*(const FVector3& r) const {
        return {
            columns[0][0] * r.x + columns[1][0] * r.y + columns[2][0] * r.z,
            columns[0][1] * r.x + columns[1][1] * r.y + columns[2][1] * r.z,
            columns[0][2] * r.x + columns[1][2] * r.y + columns[2][2] * r.z
        };
    }

    FMatrix3 FMatrix3::operator/(TReal r) const {
        return FMatrix3(*this) /= r;
    }

    FMatrix3 FMatrix3::operator/(const FMatrix3& r) const {
        return FMatrix3(*this) /= r;
    }

    FVector3 FMatrix3::operator/(const FVector3& r) const {
        return inverse(*this) * r;
    }

    FVector3& FMatrix3::operator[](TInt32 i) {
        return columns[i];
    }

    FVector3 FMatrix3::operator[](TInt32 i) const {
        return columns[i];
    }

    FMatrix3 operator+(TReal a, const FMatrix3& b) {
        return FMatrix3(a) += b;
    }

    FMatrix3 operator-(TReal a, const FMatrix3& b) {
        return FMatrix3(a) -= b;
    }

    FMatrix3 operator*(TReal a, const FMatrix3& b) {
        return FMatrix3(a) *= b;
    }

    FVector3 operator*(const FVector3& a, const FMatrix3& b) {
        return {
            b[0][0] * a.x + b[0][1] * a.y + b[0][2] * a.z,
            b[1][0] * a.x + b[1][1] * a.y + b[1][2] * a.z,
            b[2][0] * a.x + b[2][1] * a.y + b[2][2] * a.z
        };
    }

    FMatrix3 operator/(TReal a, const FMatrix3& b) {
        return {
            FVector3(a) / b[0],
            FVector3(a) / b[1],
            FVector3(a) / b[2]
        };
    }

    FVector3 operator/(const FVector3& a, const FMatrix3& b) {
        return a * inverse(b);
    }

}
