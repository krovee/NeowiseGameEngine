#include <Math/Math.h>

#include <intrin.h>

namespace Neowise {

	static __m128& _mm(FVector4& v) {
		return *(__m128*)(&v._data);
	}
#define _mm _mm(*this)

	const FVector4 FVector4::zero	= FVector4();
	const FVector4 FVector4::one	= FVector4(1);
	const FVector4 FVector4::up		= FVector4(0, 1, 0, 0);
	const FVector4 FVector4::left	= FVector4(-1, 0, 0, 0);
	const FVector4 FVector4::down	= FVector4(0, -1, 0, 0);
	const FVector4 FVector4::right	= FVector4(1, 0, 0, 0);
	const FVector4 FVector4::forward= FVector4(0, 0, 1, 0);
	const FVector4 FVector4::back	= FVector4(0, 0, -1, 0);

	FVector4::FVector4() : _data()
	{
	}

	FVector4::FVector4(real v) {
		_mm = _mm_set1_ps(v);
	}

	FVector4::FVector4(real x, real y, real z, real w) {
		_mm = _mm_set_ps(w, z, y, x);
	}

	FVector4::FVector4(const FVector3& xyz, real w) {
		_mm = _mm_set_ps(w, xyz[2], xyz[1], xyz[0]);
	}

	FVector4::FVector4(real x, const FVector3& yzw) {
		_mm = _mm_set_ps(yzw[2], yzw[1], yzw[0], x);
	}

	FVector4::FVector4(const FVector2& xy, const FVector2& zw) {
		_mm = _mm_set_ps(zw[1], zw[0], xy[1], xy[0]);
	}

	FVector4::FVector4(const FVector4& o) {
		_mm = _mm_load_ps(o._data);
	}

	FVector4::FVector4(FVector4&& o) {
		_mm = _mm_load_ps(o._data);
	}

	FVector4& FVector4::operator=(const FVector4& r) {
		_mm = _mm_load_ps(r._data);
		return *this;
	}

	FVector4& FVector4::operator=(FVector4&& r) {
		_mm = _mm_load_ps(r._data);
		return *this;
	}

	bool FVector4::operator==(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmpeq_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector4::operator!=(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmpneq_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector4::operator<(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmplt_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector4::operator<=(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmple_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector4::operator>(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmpgt_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector4::operator>=(const FVector4& r) const {
		return _mm_cvtss_i32(_mm_cmpge_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	FVector4& FVector4::operator+=(const FVector4& r) {
		_mm = _mm_add_ps(_mm, *(__m128*)(&r._data));
		return *this;
	}

	FVector4& FVector4::operator+=(const FVector3& r) {
		_mm = _mm_add_ps(_mm, _mm_set_ps(r[0], r[1], r[2], 0));
		return *this;
	}

	FVector4& FVector4::operator+=(const FVector2& r) {
		_data[0] += r[0];
		_data[1] += r[2];
		return *this;
	}

	FVector4& FVector4::operator+=(real r) {
		_mm = _mm_add_ps(_mm, _mm_set1_ps(r));
		return *this;
	}

	FVector4& FVector4::operator-=(const FVector4& r) {
		_mm = _mm_sub_ps(_mm, *(__m128*)(&r._data));
		return *this;
	}

	FVector4& FVector4::operator-=(const FVector3& r) {
		_mm = _mm_sub_ps(_mm, _mm_set_ps(r[0], r[1], r[2], 0));
		return *this;
	}

	FVector4& FVector4::operator-=(const FVector2& r) {
		_data[0] -= r[0];
		_data[1] -= r[2];
		return *this;
	}

	FVector4& FVector4::operator-=(real r) {
		_mm = _mm_sub_ps(_mm, _mm_set1_ps(r));
		return *this;
	}

	FVector4& FVector4::operator*=(const FVector4& r) {
		_mm = _mm_mul_ps(_mm, *(__m128*)(&r._data));
		return *this;
	}

	FVector4& FVector4::operator*=(const FVector3& r) {
		_mm = _mm_mul_ps(_mm, _mm_set_ps(r[0], r[1], r[2], 0));
		return *this;
	}

	FVector4& FVector4::operator*=(const FVector2& r) {
		_data[0] *= r[0];
		_data[1] *= r[2];
		return *this;
	}

	FVector4& FVector4::operator*=(real r) {
		_mm = _mm_mul_ps(_mm, _mm_set1_ps(r));
		return *this;
	}

	FVector4& FVector4::operator/=(const FVector4& r) {
		_mm = _mm_div_ps(_mm, *(__m128*)(&r._data));
		return *this;
	}

	FVector4& FVector4::operator/=(const FVector3& r) {
		_mm = _mm_div_ps(_mm, _mm_set_ps(r[0], r[1], r[2], 0));
		return *this;
	}

	FVector4& FVector4::operator/=(const FVector2& r) {
		_data[0] /= r[0];
		_data[1] /= r[2];
		return *this;
	}

	FVector4& FVector4::operator/=(real r) {
		_mm = _mm_div_ps(_mm, _mm_set1_ps(r));
		return *this;
	}

	FVector4 FVector4::operator-() const {
		return { -x, -y, -z, -w };
	}

	FVector4::operator FVector3() const {
		return xyz;
	}

	FVector4::operator FVector2() const {
		return xy;
	}

	FVector4 FVector4::operator+(const FVector4& r) const {
		return FVector4(*this) += r;
	}

	FVector4 FVector4::operator+(const FVector3& r) const {
		return FVector4(*this) += r;
	}

	FVector4 FVector4::operator+(const FVector2& r) const {
		return FVector4(*this) += r;
	}

	FVector4 FVector4::operator+(real r) const {
		return FVector4(*this) += r;
	}

	FVector4 FVector4::operator-(const FVector4& r) const {
		return FVector4(*this) -= r;
	}

	FVector4 FVector4::operator-(const FVector3& r) const {
		return FVector4(*this) -= r;
	}

	FVector4 FVector4::operator-(const FVector2& r) const {
		return FVector4(*this) -= r;
	}

	FVector4 FVector4::operator-(real r) const {
		return FVector4(*this) -= r;
	}

	FVector4 FVector4::operator*(const FVector4& r) const {
		return FVector4(*this) *= r;
	}

	FVector4 FVector4::operator*(const FVector3& r) const {
		return FVector4(*this) *= r;
	}

	FVector4 FVector4::operator*(const FVector2& r) const {
		return FVector4(*this) *= r;
	}

	FVector4 FVector4::operator*(real r) const {
		return FVector4(*this) *= r;
	}

	FVector4 FVector4::operator/(const FVector4& r) const {
		return FVector4(*this) /= r;
	}

	FVector4 FVector4::operator/(const FVector3& r) const {
		return FVector4(*this) /= r;
	}

	FVector4 FVector4::operator/(const FVector2& r) const {
		return FVector4(*this) /= r;
	}

	FVector4 FVector4::operator/(real r) const {
		return FVector4(*this) /= r;
	}

	real& FVector4::operator[](int32 i) {
		return _data[i];
	}

	real FVector4::operator[](int32 i) const {
		return _data[i];
	}

}
