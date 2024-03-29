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
		explicit FMatrix3(real v);
		FMatrix3(
			real x0, real y0, real z0,
			real x1, real y1, real z1,
			real x2, real y2, real z2
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
		FMatrix3& operator+=(real r);
		FMatrix3& operator-=(const FMatrix3& r);
		FMatrix3& operator-=(const FVector4& r);
		FMatrix3& operator-=(const FVector3& r);
		FMatrix3& operator-=(const FVector2& r);
		FMatrix3& operator-=(real r);
		FMatrix3& operator*=(const FMatrix3& r);
		FMatrix3& operator*=(const FVector4& r);
		FMatrix3& operator*=(const FVector3& r);
		FMatrix3& operator*=(const FVector2& r);
		FMatrix3& operator*=(real r);
		FMatrix3& operator/=(const FMatrix3& r);
		FMatrix3& operator/=(const FVector4& r);
		FMatrix3& operator/=(const FVector3& r);
		FMatrix3& operator/=(const FVector2& r);
		FMatrix3& operator/=(real r);

		FMatrix3 operator-() const;

		operator FQuaternion() const;

		FMatrix3 operator+(real r) const;
		FMatrix3 operator+(const FMatrix3& r) const;
		FMatrix3 operator-(real r) const;
		FMatrix3 operator-(const FMatrix3& r) const;
		FMatrix3 operator*(real r) const;
		FMatrix3 operator*(const FMatrix3& r) const;
		FVector3 operator*(const FVector3& r) const;
		FMatrix3 operator/(real r) const;
		FMatrix3 operator/(const FMatrix3& r) const;
		FVector3 operator/(const FVector3& r) const;

		FVector3& operator[](int32 i);
		FVector3 operator[](int32 i) const;

		FVector3 columns[3] = {};
	};

	FMatrix3 operator+(real a, const FMatrix3& b);
	FMatrix3 operator-(real a, const FMatrix3& b);
	FMatrix3 operator*(real a, const FMatrix3& b);
	FVector3 operator*(const FVector3& a, const FMatrix3& b);
	FMatrix3 operator/(real a, const FMatrix3& b);
	FVector3 operator/(const FVector3& a, const FMatrix3& b);


	using FMat3 = FMatrix3;


}
