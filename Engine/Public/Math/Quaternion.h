#pragma once

#include "Vector4.h"

namespace Neowise {
	/** 
	* 
	*/
	struct NW_API FQuaternion {
		~FQuaternion() = default;

		constexpr FQuaternion() : _data() {}
		FQuaternion(real x, real y, real z, real w);
		FQuaternion(const FVector3& eulerAngles);
		FQuaternion(const FVector3& normalized1, const FVector3& normalized2);

		FQuaternion(const FQuaternion&) = default;
		FQuaternion(FQuaternion&&) = default;
		FQuaternion& operator=(const FQuaternion&) = default;
		FQuaternion& operator=(FQuaternion&&) = default;

		bool operator==(const FQuaternion&) const;
		bool operator!=(const FQuaternion&) const;

		FQuaternion& operator+=(const FQuaternion&);
		FQuaternion& operator-=(const FQuaternion&);
		FQuaternion& operator*=(const FQuaternion&);
		FQuaternion& operator*=(real);
		FQuaternion& operator/=(real);

		FQuaternion operator-() const;

		// operator FMatrix3() const;
		// operator FMatrix4() const;

		FQuaternion operator+(const FQuaternion&) const;
		FQuaternion operator-(const FQuaternion&) const;
		FQuaternion operator*(const FQuaternion&) const;
		FVector3 operator*(const FVector3&) const;
		FVector4 operator*(const FVector4&) const;
		FQuaternion operator*(real) const;
		FQuaternion operator/(real) const;


		union {
			real _data[4] = {};
			struct {
				real x, y, z, w;
			};
		};

	};

	FVector3 operator*(const FVector3&, const FQuaternion&);
	FVector4 operator*(const FVector4&, const FQuaternion&);
	FQuaternion operator*(real, const FQuaternion&);

}
