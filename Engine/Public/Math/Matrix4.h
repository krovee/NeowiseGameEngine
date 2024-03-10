#pragma once

#include "Matrix3.h"

namespace Neowise {
	/**
	*
	*/
	struct NW_API FMatrix4 {
		~FMatrix4() = default;

		constexpr FMatrix4() = default;
		explicit FMatrix4(real v);
		FMatrix4(
			real x0, real y0, real z0, real  w0,
			real x1, real y1, real z1, real  w1,
			real x2, real y2, real z2, real  w2,
			real x3, real y3, real z3, real  w3
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
		FMatrix4& operator+=(real r);
		FMatrix4& operator-=(const FMatrix4& r);
		FMatrix4& operator-=(const FMatrix3& r);
		FMatrix4& operator-=(const FVector4& r);
		FMatrix4& operator-=(const FVector3& r);
		FMatrix4& operator-=(const FVector2& r);
		FMatrix4& operator-=(real r);
		FMatrix4& operator*=(const FMatrix4& r);
		FMatrix4& operator*=(const FMatrix3& r);
		FMatrix4& operator*=(const FVector4& r);
		FMatrix4& operator*=(const FVector3& r);
		FMatrix4& operator*=(const FVector2& r);
		FMatrix4& operator*=(real r);
		FMatrix4& operator/=(const FMatrix4& r);
		FMatrix4& operator/=(const FMatrix3& r);
		FMatrix4& operator/=(const FVector4& r);
		FMatrix4& operator/=(const FVector3& r);
		FMatrix4& operator/=(const FVector2& r);
		FMatrix4& operator/=(real r);

		FMatrix4 operator-() const;

		operator FQuaternion() const;

		FMatrix4 operator+(real r) const;
		FMatrix4 operator+(const FVector2& r) const;
		FMatrix4 operator+(const FVector3& r) const;
		FMatrix4 operator+(const FVector4& r) const;
		FMatrix4 operator+(const FMatrix3& r) const;
		FMatrix4 operator+(const FMatrix4& r) const;
		FMatrix4 operator-(real r) const;
		FMatrix4 operator-(const FVector2& r) const;
		FMatrix4 operator-(const FVector3& r) const;
		FMatrix4 operator-(const FVector4& r) const;
		FMatrix4 operator-(const FMatrix3& r) const;
		FMatrix4 operator-(const FMatrix4& r) const;
		FMatrix4 operator*(real r) const;
		FVector2 operator*(const FVector2& r) const;
		FVector3 operator*(const FVector3& r) const;
		FVector4 operator*(const FVector4& r) const;
		FMatrix3 operator*(const FMatrix3& r) const;
		FMatrix4 operator*(const FMatrix4& r) const;
		FMatrix4 operator/(real r) const;
		FVector2 operator / (const FVector2 & r) const;
		FVector3 operator / (const FVector3 & r) const;
		FVector4 operator/(const FVector4& r) const;
		FMatrix3 operator/(const FMatrix3& r) const;
		FMatrix4 operator/(const FMatrix4& r) const;

		FVector4& operator[](int32 i);
		FVector4 operator[](int32 i) const;

		FVector4 columns[4] = {};
	};

	FMatrix4 operator+(real a, const FMatrix4& b);
	FMatrix4 operator-(real a, const FMatrix4& b);
	FMatrix4 operator*(real a, const FMatrix4& b);
	FVector4 operator*(const FVector4& a, const FMatrix4& b);
	FMatrix4 operator/(real a, const FMatrix4& b);
	FVector4 operator/(const FVector4& a, const FMatrix4& b);

	using FMat4 = FMatrix4;


}
