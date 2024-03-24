#pragma once

#include "Vector3.h"

namespace Neowise {
	/** 
	* 
	*/
	struct NW_API FVector4 {

		~FVector4() = default;

		FVector4() : _data() {}
		explicit FVector4(real o);
		FVector4(real x, real y, real z, real w);
		FVector4(const FVector3& xyz, real w);
		FVector4(real x, const FVector3& yzw);
		FVector4(const FVector2& xy, const FVector2& zw);

		FVector4(const FVector4&);
		FVector4(FVector4&&);
		FVector4& operator=(const FVector4&);
		FVector4& operator=(FVector4&&);

		bool operator==(const FVector4&) const;
		bool operator!=(const FVector4&) const;
		bool operator<(const FVector4&) const;
		bool operator<=(const FVector4&) const;
		bool operator>(const FVector4&) const;
		bool operator>=(const FVector4&) const;

		FVector4& operator+=(const FVector4&);
		FVector4& operator+=(const FVector3&);
		FVector4& operator+=(const FVector2&);
		FVector4& operator+=(real);
		FVector4& operator-=(const FVector4&);
		FVector4& operator-=(const FVector3&);
		FVector4& operator-=(const FVector2&);
		FVector4& operator-=(real);
		FVector4& operator*=(const FVector4&);
		FVector4& operator*=(const FVector3&);
		FVector4& operator*=(const FVector2&);
		FVector4& operator*=(real);
		FVector4& operator/=(const FVector4&);
		FVector4& operator/=(const FVector3&);
		FVector4& operator/=(const FVector2&);
		FVector4& operator/=(real);

		FVector4 operator-() const;

		operator FVector3() const;
		operator FVector2() const;

		FVector4 operator+(const FVector4&) const;
		FVector4 operator+(const FVector3&) const;
		FVector4 operator+(const FVector2&) const;
		FVector4 operator+(real) const;
		FVector4 operator-(const FVector4&) const;
		FVector4 operator-(const FVector3&) const;
		FVector4 operator-(const FVector2&) const;
		FVector4 operator-(real) const;
		FVector4 operator*(const FVector4&) const;
		FVector4 operator*(const FVector3&) const;
		FVector4 operator*(const FVector2&) const;
		FVector4 operator*(real) const;
		FVector4 operator/(const FVector4&) const;
		FVector4 operator/(const FVector3&) const;
		FVector4 operator/(const FVector2&) const;
		FVector4 operator/(real) const;

		real& operator[](int32 i);
		real operator[](int32 i) const;

		static const FVector4 zero;
		static const FVector4 one;
		static const FVector4 up;
		static const FVector4 left;
		static const FVector4 down;
		static const FVector4 right;
		static const FVector4 forward;
		static const FVector4 back;

		union {
			__m128 _mm = {};
			real _data[4];
			FVector3 rgb;
			FVector3 xyz;
			FVector2 xy;
			struct {
				real x;
				union {
					struct {
						real y;
						union {
							struct {
								real z;
								real w;
							};
						};
					};
				};
			};
			struct {
				real r, g, b, a;
			};
		};

	};

	using FVec4 = FVector4;

}
