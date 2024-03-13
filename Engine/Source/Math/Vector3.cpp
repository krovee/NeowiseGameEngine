#include <Math/Math.h>

#include <immintrin.h>

#ifndef _mm_cvtss_i32_safe
#	if NW_OS(LINUX)
#		define _mm_cvtss_i32_safe __builtin_ia32_cvtss2si
#	else
#		define _mm_cvtss_i32_safe _mm_cvtss_i32
#	endif
#endif

namespace Neowise {

	FVector3::operator FVector2() const {
		return xy;
	}

	const FVector3 FVector3::zero	= FVector3();
	const FVector3 FVector3::one	= FVector3(1);
	const FVector3 FVector3::up		= FVector3(0, 1, 0);
	const FVector3 FVector3::left	= FVector3(-1, 0, 0);
	const FVector3 FVector3::down	= FVector3(0, -1, 0);
	const FVector3 FVector3::right	= FVector3(1, 0, 0);
	const FVector3 FVector3::forward= FVector3(0, 0, 1);
	const FVector3 FVector3::back	= FVector3(0, 0, -1);

	FVector3 FVector3::operator+(const FVector3& r) const {
		return FVector3(*this) += r;
	}

	FVector3 FVector3::operator+(const FVector2& r) const {
		return FVector3(*this) += r;
	}

	FVector3 FVector3::operator+(real r) const {
		return FVector3(*this) += r;
	}

	FVector3 FVector3::operator-(const FVector3& r) const {
		return FVector3(*this) -= r;
	}

	FVector3 FVector3::operator-(const FVector2& r) const {
		return FVector3(*this) -= r;
	}

	FVector3 FVector3::operator-(real r) const {
		return FVector3(*this) -= r;
	}

	FVector3 FVector3::operator*(const FVector3& r) const {
		return FVector3(*this) *= r;
	}

	FVector3 FVector3::operator*(const FVector2& r) const {
		return FVector3(*this) *= r;
	}

	FVector3 FVector3::operator*(real r) const {
		return FVector3(*this) *= r;
	}

	FVector3 FVector3::operator/(const FVector3& r) const {
		return FVector3(*this) /= r;
	}

	FVector3 FVector3::operator/(const FVector2& r) const {
		return FVector3(*this) /= r;
	}

	FVector3 FVector3::operator/(real r) const {
		return FVector3(*this) /= r;
	}

	real& FVector3::operator[](int32 i) {
		return _data[i];
	}

	real FVector3::operator[](int32 i) const {
		return _data[i];
	}

	FVector3::FVector3(real v) : _data{ v, v, v }
	{
	}

	FVector3::FVector3(real x, real y, real z) : _data{ x, y, z }
	{
	}

	FVector3::FVector3(const FVector2& xy, real z) : _data{ xy[0], xy[1], z }
	{
	}

	FVector3::FVector3(real x, const FVector2& yz) : _data{ x, yz[0], yz[1] }
	{
	}

	FVector3::FVector3(const FVector3& o) : _data{ o[0], o[1], o[2] }
	{
	}

	FVector3::FVector3(FVector3&& o) : _data{ o[0], o[1], o[2] }
	{
	}

	FVector3& FVector3::operator=(const FVector3& r) {
		_data[0] = r[0];
		_data[1] = r[1];
		_data[2] = r[2];
		return *this;
	}

	FVector3& FVector3::operator=(FVector3&& r) {
		_data[0] = r[0];
		_data[1] = r[1];
		_data[2] = r[2];
		return *this;
	}

	bool FVector3::operator==(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmpeq_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector3::operator!=(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmpneq_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector3::operator<(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmplt_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector3::operator<=(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmple_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector3::operator>(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmpgt_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	bool FVector3::operator>=(const FVector3& r) const {
		return _mm_cvtss_i32_safe(_mm_cmpge_ps(_mm_load_ps(_data), _mm_load_ps(r._data)));
	}

	FVector3& FVector3::operator+=(const FVector3& r) {
		_data[0] += r[0];
		_data[1] += r[1];
		_data[2] += r[2];
		return *this;
	}

	FVector3& FVector3::operator+=(const FVector2& r) {
		_data[0] += r[0];
		_data[2] += r[1];
		return *this;
	}

	FVector3& FVector3::operator+=(real r) {
		_data[0] += r;
		_data[1] += r;
		return *this;
	}

	FVector3& FVector3::operator-=(const FVector3& r) {
		_data[0] -= r[0];
		_data[1] -= r[1];
		_data[2] -= r[2];
		return *this;
	}

	FVector3& FVector3::operator-=(const FVector2& r) {
		_data[0] -= r[0];
		_data[2] -= r[1];
		return *this;
	}

	FVector3& FVector3::operator-=(real r) {
		_data[0] -= r;
		_data[1] -= r;
		return *this;
	}

	FVector3& FVector3::operator*=(const FVector3& r) {
		_data[0] *= r[0];
		_data[1] *= r[1];
		_data[2] *= r[2];
		return *this;
	}

	FVector3& FVector3::operator*=(const FVector2& r) {
		_data[0] *= r[0];
		_data[2] *= r[1];
		return *this;
	}

	FVector3& FVector3::operator*=(real r) {
		_data[0] *= r;
		_data[1] *= r;
		return *this;
	}

	FVector3& FVector3::operator/=(const FVector3& r) {
		_data[0] /= r[0];
		_data[1] /= r[1];
		_data[2] /= r[2];
		return *this;
	}

	FVector3& FVector3::operator/=(const FVector2& r) {
		_data[0] /= r[0];
		_data[2] /= r[1];
		return *this;
	}

	FVector3& FVector3::operator/=(real r) {
		_data[0] /= r;
		_data[1] /= r;
		return *this;
	}

	FVector3 FVector3::operator-() const {
		return { -_data[0], -_data[1], -_data[2] };
	}

}
