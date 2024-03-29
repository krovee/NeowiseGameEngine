#include <Math/Vector2.h>

namespace Neowise {
	const FVector2 FVector2::zero	= {0, 0};
	const FVector2 FVector2::one 	= {1, 1};
	const FVector2 FVector2::left 	= {-1, 0};
	const FVector2 FVector2::right 	= {1, 0};

	FVector2::FVector2(real v)
		: _data{ v, v }
	{
	}

	FVector2::FVector2(real x, real y)
		: _data{ x, y }
	{
	}
	
	FVector2::FVector2(const FVector2& o)
		: _data{ o.x, o.y }
	{
	}
	
	FVector2::FVector2(FVector2&& o) 
		: _data{ o.x, o.y }
	{
	}
	
	FVector2& FVector2::operator=(const FVector2& r) {
		_data[0] = r._data[0];
		_data[1] = r._data[1];
		return *this;
	}
	
	FVector2& FVector2::operator=(FVector2&& r) {
		_data[0] = r._data[0];
		_data[1] = r._data[1];
		return *this;
	}
	
	bool FVector2::operator==(const FVector2& r) const {
		return x == r.x && y == r.y;
	}
	
	bool FVector2::operator!=(const FVector2& r) const {
		return !(*this == r);
	}
	
	bool FVector2::operator<(const FVector2& r) const {
		return x < r.x && y < r.y;
	}
	
	bool FVector2::operator<=(const FVector2& r) const {
		return x <= r.x && y <= r.y;
	}
	
	bool FVector2::operator>(const FVector2& r) const {
		return x > r.x && y > r.y;
	}
	
	bool FVector2::operator>=(const FVector2& r) const {
		return x >= r.x && y >= r.y;
	}
	
	FVector2& FVector2::operator+=(const FVector2& r) {
		x += r.x;
		y += r.y;
		return *this;
	}
	
	FVector2& FVector2::operator+=(real r) {
		x += r;
		y += r;
		return *this;
	}
	
	FVector2& FVector2::operator-=(const FVector2& r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}
	
	FVector2& FVector2::operator-=(real r) {
		x -= r;
		y -= r;
		return *this;
	}
	
	FVector2& FVector2::operator*=(const FVector2& r) {
		x *= r.x;
		y *= r.y;
		return *this;
	}
	
	FVector2& FVector2::operator*=(real r) {
		x *= r;
		y *= r;
		return *this;
	}
	
	FVector2& FVector2::operator/=(const FVector2& r) {
		x /= r.x;
		y /= r.y;
		return *this;
	}
	
	FVector2& FVector2::operator/=(real r) {
		x /= r;
		y /= r;
		return *this;
	}
	
	FVector2 FVector2::operator-() const {
		return { -x, -y };
	}
	
	FVector2 FVector2::operator+(const FVector2& r) const {
		return FVector2(*this) += r;
	}
	
	FVector2 FVector2::operator+(real r) const {
		return FVector2(*this) += r;
	}
	
	FVector2 FVector2::operator-(const FVector2& r) const {
		return FVector2(*this) -= r;
	}
	
	FVector2 FVector2::operator-(real r) const {
		return FVector2(*this) -= r;
	}
	
	FVector2 FVector2::operator*(const FVector2& r) const {
		return FVector2(*this) *= r;
	}
	
	FVector2 FVector2::operator*(real r) const {
		return FVector2(*this) *= r;
	}
	
	FVector2 FVector2::operator/(const FVector2& r) const {
		return FVector2(*this) /= r;
	}
	
	FVector2 FVector2::operator/(real r) const {
		return FVector2(*this) /= r;
	}
	
	real& FVector2::operator[](int32 i) {
		return _data[i];
	}
	
	real FVector2::operator[](int32 i) const {
		return _data[i];
	}

	FVector2 operator+(const real a, const FVector2& b) {
		return FVector2(a) + b;
	}

	FVector2 operator-(const real a, const FVector2& b) {
		return FVector2(a) - b;
	}

	FVector2 operator*(const real a, const FVector2& b) {
		return FVector2(a) * b;
	}

	FVector2 operator/(const real a, const FVector2& b) {
		return FVector2(a) / b;
	}


}
