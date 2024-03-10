#pragma once

#include "Scalar.h"

namespace Neowise {
	/** 
	* Linear algebra math vector2 representation structure.
	*/
	struct NW_API FVector2 {

		~FVector2() = default;

		constexpr FVector2() = default;
		explicit FVector2(real v);
		FVector2(real x, real y);

		FVector2(const FVector2&);
		FVector2(FVector2&&);
		FVector2& operator=(const FVector2&);
		FVector2& operator=(FVector2&&);

		bool operator==(const FVector2&) const;
		bool operator!=(const FVector2&) const;
		bool operator<(const FVector2&) const;
		bool operator<=(const FVector2&) const;
		bool operator>(const FVector2&) const;
		bool operator>=(const FVector2&) const;

		FVector2& operator+=(const FVector2&);
		FVector2& operator+=(real);
		FVector2& operator-=(const FVector2&);
		FVector2& operator-=(real);
		FVector2& operator*=(const FVector2&);
		FVector2& operator*=(real);
		FVector2& operator/=(const FVector2&);
		FVector2& operator/=(real);

		FVector2 operator-() const;

		FVector2 operator+(const FVector2&) const;
		FVector2 operator+(real) const;
		FVector2 operator-(const FVector2&) const;
		FVector2 operator-(real) const;
		FVector2 operator*(const FVector2&) const;
		FVector2 operator*(real) const;
		FVector2 operator/(const FVector2&) const;
		FVector2 operator/(real) const;

		real& operator[](int32 i);
		real  operator[](int32 i) const;

		static const FVector2 zero;
		static const FVector2 one;
		static const FVector2 up;
		static const FVector2 left;
		static const FVector2 down;
		static const FVector2 right;

		union {
			real _data[2] = {};
			struct { real x, y; };
			struct { real u, v; };
			struct { real r, g; };
		};
	};

	using FVec2 = FVector2;
}
