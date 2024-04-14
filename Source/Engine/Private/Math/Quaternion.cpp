#include "Math/Quaternion.h"
#include "Math/Vector2.h"
#include <Math/Math.h>

#include  <immintrin.h>

namespace Neowise {

    FQuaternion::FQuaternion(TReal x, TReal y, TReal z, TReal w)
        : x(x), y(y), z(z), w(w)
    {
    }

    FQuaternion::FQuaternion(const FVector3& eulerAngles) {
        const auto cv = cos(eulerAngles * TReal(.5));
        const auto sv = sin(eulerAngles * TReal(.5));

        x = sv.x * cv.y * cv.z - cv.x * sv.y * sv.z;
        y = cv.x * sv.y * cv.z + sv.x * cv.y * sv.z;
        z = cv.x * cv.y * sv.z - sv.x * sv.y * cv.z;
        w = cv.x * cv.y * cv.z + sv.x * sv.y * sv.z;
    }

    FQuaternion::FQuaternion(const FVector3& axis, const TReal angle) {
        const auto xyz = axis * sin(angle * TReal(.5));
        w = cos(angle * TReal(.5));
        x = xyz.x;
        y = xyz.y;
        z = xyz.z;
    }

    //FQuaternion::FQuaternion(const FQuaternion& o)
    //	: _data{ o.x, o.y, o.z, o.w }
    //{
    //}

    //FQuaternion::FQuaternion(const FVector3& normalized1, const FVector3& normalized2) {
    //	const auto normUV = sqrt(dot(normalized1, normalized1) * dot(normalized2, normalized2));
    //	auto realPart = normUV + dot(normalized1, normalized2);
    //}

    bool FQuaternion::operator==(const FQuaternion& r) const {
        return *(FVector4*)(this) == *(FVector4*)(&r);
    }

    bool FQuaternion::operator!=(const FQuaternion& r) const {
        return *(FVector4*)(this) != *(FVector4*)(&r);
    }

    FQuaternion& FQuaternion::operator+=(const FQuaternion& r) {
        *(FVector4*)(this) += *(FVector4*)(&r);
        return *this;
    }

    FQuaternion& FQuaternion::operator-=(const FQuaternion& r) {
        *(FVector4*)(this) -= *(FVector4*)(&r);
        return *this;
    }

    FQuaternion& FQuaternion::operator*=(const FQuaternion& r) {
        const auto p(*this);
        const auto& q(r);

        x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
        y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
        z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
        w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        return *this;
    }

    FQuaternion& FQuaternion::operator*=(TReal r) {
        *(FVector4*)(this) *= r;
        return *this;
    }

    FQuaternion& FQuaternion::operator/=(TReal r) {
        *(FVector4*)(this) /= r;
        return *this;
    }

    FQuaternion FQuaternion::operator-() const {
        return { -x, -y, -z, -w };
    }

    FQuaternion FQuaternion::operator+(const FQuaternion& r) const {
        return FQuaternion(*this)    += r;
    }

    FQuaternion FQuaternion::operator-(const FQuaternion& r) const {
        return FQuaternion(*this)    += r;
    }

    FQuaternion FQuaternion::operator*(const FQuaternion& r) const {
        return FQuaternion(*this)    *= r;
    }

    FVector3 FQuaternion::operator*(const FVector3& r) const {
        const FVector3 qv = { x, y, z };
        const auto     uv = cross(qv, r);
        const auto    uuv = cross(qv, uv);
        return r + ((uv * w) + uuv) * (TReal)(2);
    }

    FVector4 FQuaternion::operator*(const FVector4& v) const {
        const auto& q(*this);

        const auto q_wwww = _mm_shuffle_ps(*(__m128*)(&q._data), *(__m128*)(&q._data), _MM_SHUFFLE(3, 3, 3, 3));
        const auto q_swp0 = _mm_shuffle_ps(*(__m128*)(&q._data), *(__m128*)(&q._data), _MM_SHUFFLE(3, 0, 2, 1));
        const auto q_swp1 = _mm_shuffle_ps(*(__m128*)(&q._data), *(__m128*)(&q._data), _MM_SHUFFLE(3, 1, 0, 2));
        const auto v_swp0 = _mm_shuffle_ps(*(__m128*)(&v._data), *(__m128*)(&v._data), _MM_SHUFFLE(3, 0, 2, 1));
        const auto v_swp1 = _mm_shuffle_ps(*(__m128*)(&v._data), *(__m128*)(&v._data), _MM_SHUFFLE(3, 1, 0, 2));

        __m128 uv = _mm_sub_ps(_mm_mul_ps(q_swp0, v_swp1), _mm_mul_ps(q_swp1, v_swp0));
        __m128 uv_swp0 = _mm_shuffle_ps(uv, uv, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 uv_swp1 = _mm_shuffle_ps(uv, uv, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 uuv = _mm_sub_ps(_mm_mul_ps(q_swp0, uv_swp1), _mm_mul_ps(q_swp1, uv_swp0));

        __m128 const two = _mm_set1_ps(2.0f);
        uv = _mm_mul_ps(uv, _mm_mul_ps(q_wwww, two));
        uuv = _mm_mul_ps(uuv, two);

        FVector4 r;
        *(__m128*)(&r._data) = _mm_add_ps(*(__m128*)(&v._data), _mm_add_ps(uv, uuv));
        return r;

    }

    FQuaternion FQuaternion::operator*(TReal r) const {
        return FQuaternion(*this) *= r;
    }

    FQuaternion FQuaternion::operator/(TReal r) const {
        return FQuaternion(*this) /= r;
    }

#ifndef abs
#	define abs(x) ((x) < 0 ? -(x) : (x))
#endif

    TReal FQuaternion::angle() const {
        if (abs(w) > TReal(0.877582561890372716130286068203503191)) {
            const auto a = asin(sqrt(x * x + y * y + z * z)) * TReal(2.);
            if (w < 0) {
                return Const::kRealPi * TReal(2) - a;
            }

            return a;
        }

        return acos(w) * TReal(2);
    }

    TReal FQuaternion::roll() const {
        const auto y2 = TReal(2) * (x * y * w * z);
        const auto x2 = w * w + x * x - y * y - z * z;

        if (FVector2(x2, y2) == FVector2::zero) {
            return 0;
        }

        return atan2(y2, x2);
    }

    TReal FQuaternion::pitch() const {
        const auto y2 = TReal(2) * (y * z + w * x);
        const auto x2 = w * w - x * x - y * y + z * z;

        if (FVector2(x2, y2) == FVector2::zero) {
            return TReal(2) * atan2(x, w);
        }

        return atan2(y2, x2);
    }

    TReal FQuaternion::yaw() const {
        return asin(NW_CLAMP(TReal(-2) * (x * z - w * y), TReal(-1), TReal(1)));
    }

    FVector3 FQuaternion::axis() const {
        const auto t = TReal(1) - w * w;
        if (t <= 0) {
            return { 0, 0, 1 };
        }

        const auto t2 = TReal(1) / sqrt(t);
        return { x * t2, y * t2, z * t2 };
    }

    FVector3 FQuaternion::euler() const {
        return { pitch(), yaw(), roll() };
    }

    void FQuaternion::apply(FMatrix4& m) {
        m = rotateAxis(m, axis(), angle());
    }

}
