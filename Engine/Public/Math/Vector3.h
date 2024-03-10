#pragma once

#include "Vector2.h"

namespace Neowise {
	/**
	* Linear algebra math vector3 representation structure.
	*/
	struct NW_API FVector3 {

		~FVector3() = default;

		constexpr FVector3() = default;
		explicit FVector3(real v);
		FVector3(real x, real y, real z);
		FVector3(const FVector2& xy, real z);
		FVector3(real x, const FVector2& yz);

		FVector3(const FVector3&);
		FVector3(FVector3&&);
		FVector3& operator=(const FVector3&);
		FVector3& operator=(FVector3&&); 

		bool operator==(const FVector3&) const;
		bool operator!=(const FVector3&) const;
		bool operator<(const FVector3&) const;
		bool operator<=(const FVector3&) const;
		bool operator>(const FVector3&) const;
		bool operator>=(const FVector3&) const;

		FVector3& operator+=(const FVector3&);
		FVector3& operator+=(const FVector2&);
		FVector3& operator+=(real);
		FVector3& operator-=(const FVector3&);
		FVector3& operator-=(const FVector2&);
		FVector3& operator-=(real);
		FVector3& operator*=(const FVector3&);
		FVector3& operator*=(const FVector2&);
		FVector3& operator*=(real);
		FVector3& operator/=(const FVector3&);
		FVector3& operator/=(const FVector2&);
		FVector3& operator/=(real);

		FVector3 operator-() const;

		operator FVector2() const;

		FVector3 operator+(const FVector3&) const;
		FVector3 operator+(const FVector2&) const;
		FVector3 operator+(real) const;
		FVector3 operator-(const FVector3&) const;
		FVector3 operator-(const FVector2&) const;
		FVector3 operator-(real) const;
		FVector3 operator*(const FVector3&) const;
		FVector3 operator*(const FVector2&) const;
		FVector3 operator*(real) const;
		FVector3 operator/(const FVector3&) const;
		FVector3 operator/(const FVector2&) const;
		FVector3 operator/(real) const;

		real& operator[](int32 i);
		real  operator[](int32 i) const;

		static const FVector3 zero;
		static const FVector3 one;
		static const FVector3 up;
		static const FVector3 left;
		static const FVector3 down;
		static const FVector3 right;
		static const FVector3 forward;
		static const FVector3 back;

		union {
			real _data[3] = {};
			struct { real x, y, z; };
			struct { real r, g, b; };
			struct { FVector2 xy; };
			struct { FVector2 rg; };
			struct { FVector2 uv; };
		};
	};

	using FVec3 = FVector3;
}
