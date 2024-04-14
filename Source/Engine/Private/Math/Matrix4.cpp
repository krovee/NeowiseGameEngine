#include <Math/Math.h>

//#include <intrin.h>

#include <immintrin.h>

#ifndef _mm_cvtss_i32_safe
#	if NW_OS_TYPE_LINUX
#		define _mm_cvtss_i32_safe __builtin_ia32_cvtss2si
#	else
#		define _mm_cvtss_i32_safe _mm_cvtss_i32
#	endif
#endif

namespace Neowise {

    FMatrix4::FMatrix4(TReal v) 
        : columns{
            FVector4(v, 0, 0, 0),
            FVector4(0, v, 0, 0),
            FVector4(0, 0, v, 0),
            FVector4(0, 0, 0, v)
        }
    {
    }

    FMatrix4::FMatrix4(
        TReal x0, TReal y0, TReal z0, TReal w0, 
        TReal x1, TReal y1, TReal z1, TReal w1, 
        TReal x2, TReal y2, TReal z2, TReal w2, 
        TReal x3, TReal y3, TReal z3, TReal w3)
        : columns{
            { x0, y0, z0, w0 },
            { x1, y1, z1, w1 },
            { x2, y2, z2, w2 },
            { x3, y3, z3, w3 }
        }
    {
    }

    FMatrix4::FMatrix4(const FVector4& col0, const FVector4& col1, const FVector4& col2, const FVector4& col3)
        : columns{
            col0,
            col1,
            col2,
            col3
        }
    {
    }

    bool FMatrix4::operator==(const FMatrix4& r) const {
        const auto m = (const TReal* const)(&const_cast<FMatrix4&>(*this)[0][0]);
        const auto m2= (const TReal* const)(&const_cast<FMatrix4&>(r)[0][0]);
        
        return _mm_cvtss_i32_safe(_mm256_castps256_ps128(
            _mm256_and_ps(
                _mm256_cmp_ps(
                    _mm256_set_ps(
                        m[0], m[1], m[2], m[3],
                        m[4], m[5], m[6], m[7]
                    ),
                    _mm256_set_ps(
                        m2[0], m2[1], m2[2], m2[3],
                        m2[4], m2[5], m2[6], m2[7]
                    ),
                    _CMP_EQ_OQ
                )
                ,
                _mm256_cmp_ps(
                    _mm256_set_ps(
                        m[8], m[9], m[10], m[11],
                        m[12], m[13], m[14], m[15]
                    ),
                    _mm256_set_ps(
                        m2[8], m2[9], m2[10], m2[11],
                        m2[12], m2[13], m2[14], m2[15]
                    ),
                    _CMP_EQ_OQ
                )
            )
        ));
    }

    bool FMatrix4::operator!=(const FMatrix4& r) const {
        return !(*this == r);
    }

    FMatrix4& FMatrix4::operator+=(const FMatrix4& r) {
        columns[0] += r[0];
        columns[1] += r[1];
        columns[2] += r[2];
        columns[3] += r[3];
        return *this;
    }

    FMatrix4& FMatrix4::operator+=(const FMatrix3& r) {
        columns[0] += r[0];
        columns[1] += r[1];
        columns[2] += r[2];
        return *this;
    }

    FMatrix4& FMatrix4::operator+=(const FVector4& r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        columns[3] += r;
        return *this;
    }

    FMatrix4& FMatrix4::operator+=(const FVector3& r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        columns[3] += r;
        return *this;
    }

    FMatrix4& FMatrix4::operator+=(const FVector2& r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        columns[3] += r;
        return *this;
    }

    FMatrix4& FMatrix4::operator+=(TReal r) {
        columns[0] += r;
        columns[1] += r;
        columns[2] += r;
        columns[3] += r;
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(const FMatrix4& r) {
        columns[0] -= r[0];
        columns[1] -= r[1];
        columns[2] -= r[2];
        columns[3] -= r[3];
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(const FMatrix3& r) {
        columns[0] -= r[0];
        columns[1] -= r[1];
        columns[2] -= r[2];
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(const FVector4& r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        columns[3] -= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(const FVector3& r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        columns[3] -= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(const FVector2& r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        columns[3] -= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator-=(TReal r) {
        columns[0] -= r;
        columns[1] -= r;
        columns[2] -= r;
        columns[3] -= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(const FMatrix4& r) {
        columns[0] *= r[0];
        columns[1] *= r[1];
        columns[2] *= r[2];
        columns[3] *= r[3];
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(const FMatrix3& r) {
        columns[0] *= r[0];
        columns[1] *= r[1];
        columns[2] *= r[2];
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(const FVector4& r) {
        columns[0] *= r[0];
        columns[1] *= r[1];
        columns[2] *= r[2];
        columns[3] *= r[3];
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(const FVector3& r) {
        columns[0] *= r[0];
        columns[1] *= r[1];
        columns[2] *= r[2];
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(const FVector2& r) {
        columns[0] *= r[0];
        columns[1] *= r[1];
        return *this;
    }

    FMatrix4& FMatrix4::operator*=(TReal r) {
        columns[0] *= r;
        columns[1] *= r;
        columns[2] *= r;
        columns[3] *= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(const FMatrix4& r) {
        columns[0] /= r[0];
        columns[1] /= r[1];
        columns[2] /= r[2];
        columns[3] /= r[3];
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(const FMatrix3& r) {
        columns[0] /= r[0];
        columns[1] /= r[1];
        columns[2] /= r[2];
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(const FVector4& r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        columns[3] /= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(const FVector3& r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        columns[3] /= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(const FVector2& r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        columns[3] /= r;
        return *this;
    }

    FMatrix4& FMatrix4::operator/=(TReal r) {
        columns[0] /= r;
        columns[1] /= r;
        columns[2] /= r;
        columns[3] /= r;
        return *this;
    }

    FMatrix4 FMatrix4::operator-() const {
        return {
            -columns[0],
            -columns[1],
            -columns[2],
            -columns[3]
        };
    }

    FMatrix4::operator FQuaternion() const {
        return FMatrix3(*this);
    }

    FMatrix4 FMatrix4::operator+(TReal r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator+(const FVector2& r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator+(const FVector3& r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator+(const FVector4& r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator+(const FMatrix3& r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator+(const FMatrix4& r) const {
        return FMatrix4(*this) += r;
    }

    FMatrix4 FMatrix4::operator-(TReal r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator-(const FVector2& r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator-(const FVector3& r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator-(const FVector4& r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator-(const FMatrix3& r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator-(const FMatrix4& r) const {
        return FMatrix4(*this) -= r;
    }

    FMatrix4 FMatrix4::operator*(TReal r) const {
        return FMatrix4(*this) *= r;
    }

    FVector2 FMatrix4::operator*(const FVector2& r) const {
        const FVector2 mv0(r[0]);
        const FVector2 mv1(r[1]);
        const FVector2 ml0 = columns[0] * mv0;
        const FVector2 ml1 = columns[1] * mv1;
        const FVector2 add0 = ml0 + ml1;
        const FVector2 mv2(r[2]);
        const FVector2 mv3(r[3]);
        const FVector2 ml2 = columns[2] * mv2;
        const FVector2 ml3 = columns[3] * mv3;
        const FVector2 add1 = ml2 + ml3;
        const FVector2 add2 = add0 + add1;
        return add2;
    }

    FVector3 FMatrix4::operator*(const FVector3& r) const {
        const FVector3 mv0(r[0]);
        const FVector3 mv1(r[1]);
        const FVector3 ml0 = columns[0] * mv0;
        const FVector3 ml1 = columns[1] * mv1;
        const FVector3 add0 = ml0 + ml1;
        const FVector3 mv2(r[2]);
        const FVector3 mv3(r[3]);
        const FVector3 ml2 = columns[2] * mv2;
        const FVector3 ml3 = columns[3] * mv3;
        const FVector3 add1 = ml2 + ml3;
        const FVector3 add2 = add0 + add1;
        return add2;
    }

    FVector4 FMatrix4::operator*(const FVector4& r) const {
        const FVector4 mv0(r[0]);
        const FVector4 mv1(r[1]);
        const FVector4 ml0 = columns[0] * mv0;
        const FVector4 ml1 = columns[1] * mv1;
        const FVector4 add0 = ml0 + ml1;
        const FVector4 mv2(r[2]);
        const FVector4 mv3(r[3]);
        const FVector4 ml2 = columns[2] * mv2;
        const FVector4 ml3 = columns[3] * mv3;
        const FVector4 add1 = ml2 + ml3;
        const FVector4 add2 = add0 + add1;
        return add2;
    }

    FMatrix4 FMatrix4::operator*(const FMatrix4& r) const {
        const FVector4& a0 = columns[0];
        const FVector4& a1 = columns[1];
        const FVector4& a2 = columns[2];
        const FVector4& a3 = columns[3];

        const FVector4& b0 = r[0];
        const FVector4& b1 = r[1];
        const FVector4& b2 = r[2];
        const FVector4& b3 = r[3];

        FMatrix4 res;
        res[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
        res[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
        res[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
        res[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
        return res;
    }

    FMatrix4 FMatrix4::operator/(TReal r) const {
        return {
            columns[0] / r,
            columns[1] / r,
            columns[2] / r,
            columns[3] / r
        };
    }

    FVector2 FMatrix4::operator/(const FVector2& r) const {
        return inverse(*this) * r;
    }

    FVector3 FMatrix4::operator/(const FVector3& r) const {
        return inverse(*this) * r;
    }

    FVector4 FMatrix4::operator/(const FVector4& r) const {
        return inverse(*this) * r;
    }

    FMatrix4 FMatrix4::operator/(const FMatrix4& r) const {
        return FMatrix4(*this) /= r;
    }

    FMatrix3 FMatrix4::operator/(const FMatrix3& r) const {
        return FMatrix3(*this) /= r;
    }

    FMatrix3 FMatrix4::operator*(const FMatrix3& r) const {
        const FVector4& a0 = columns[0];
        const FVector4& a1 = columns[1];
        const FVector4& a2 = columns[2];
        const FVector4& a3 = columns[3];

        const FVector3& b0 = r[0];
        const FVector3& b1 = r[1];
        const FVector3& b2 = r[2];
        const FVector3& b3 = r[3];

        FMatrix3 res;
        res[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
        res[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
        res[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
        res[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
        return res;
    }

    FVector4& FMatrix4::operator[](TInt32 i) {
        return columns[i];
    }

    FVector4 FMatrix4::operator[](TInt32 i) const {
        return columns[i];
    }

    FMatrix4 operator+(TReal a, const FMatrix4& b) {
        return {
            FVector4(a) += b[0],
            FVector4(a) += b[1],
            FVector4(a) += b[2],
            FVector4(a) += b[3]
        };
    }

    FMatrix4 operator-(TReal a, const FMatrix4& b) {
        return {
            FVector4(a) -= b[0],
            FVector4(a) -= b[1],
            FVector4(a) -= b[2],
            FVector4(a) -= b[3]
        };
    }

    FMatrix4 operator*(TReal a, const FMatrix4& b) {
        return {
            FVector4(a) *= b[0],
            FVector4(a) *= b[1],
            FVector4(a) *= b[2],
            FVector4(a) *= b[3]
        };
    }

    FVector4 operator*(const FVector4& a, const FMatrix4& b) {
        return {
            b[0][0] * a[0] + b[0][1] * a[1] + b[0][2] * a[2] + b[0][3] * a[3],
            b[1][0] * a[0] + b[1][1] * a[1] + b[1][2] * a[2] + b[1][3] * a[3],
            b[2][0] * a[0] + b[2][1] * a[1] + b[2][2] * a[2] + b[2][3] * a[3],
            b[3][0] * a[0] + b[3][1] * a[1] + b[3][2] * a[2] + b[3][3] * a[3]
        };
    }

    FMatrix4 operator/(TReal a, const FMatrix4& b) {
        return {
            FVector4(a) /= b[0],
            FVector4(a) /= b[1],
            FVector4(a) /= b[2],
            FVector4(a) /= b[3]
        };
    }

    FVector4 operator/(const FVector4& a, const FMatrix4& b) {
        return a * inverse(b);
    }

}
