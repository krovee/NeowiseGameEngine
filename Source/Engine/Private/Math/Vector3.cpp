#include <Math/Math.h>

namespace Neowise {

	FVector3::operator FVector2() const {
		return xy;
	}

	//									 R     F    U
	const FVector3 FVector3::zero	= {0, 0, 0};
	const FVector3 FVector3::one	= {1, 1, 1};
	const FVector3 FVector3::up		= {0, 0, 1};
	const FVector3 FVector3::left	= {-1, 0, 0};
	const FVector3 FVector3::down	= {0, 0, -1};
	const FVector3 FVector3::right	= {1, 0, 0};
	const FVector3 FVector3::forward= {0, 1, 0};
	const FVector3 FVector3::back	= {0, -1, 0};

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

	FVector3 operator+(const real a, const FVector3& b) {
		return FVector3(a) + b;
	}

	FVector3 operator-(const real a, const FVector3& b) {
		return FVector3(a) - b;
	}

	FVector3 operator*(const real a, const FVector3& b) {
		return FVector3(a) * b;
	}

	FVector3 operator/(const real a, const FVector3& b) {
		return FVector3(a) / b;
	}


}