#include <Math/Math.h>

namespace Neowise {

	FMatrix3 inverse(const FMatrix3& m) {
		const auto tmp = (real)(1) / (
			+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

		FMatrix3 im;
		im[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * tmp;
		im[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * tmp;
		im[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * tmp;
		im[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * tmp;
		im[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * tmp;
		im[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * tmp;
		im[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * tmp;
		im[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * tmp;
		im[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * tmp;

		return im;
	}

	FMatrix3 transpose(const FMatrix3& m) {
		FMatrix3 rm(1);
		rm[0][0] = m[0][0];
		rm[0][1] = m[1][0];
		rm[0][2] = m[2][0];

		rm[1][0] = m[0][1];
		rm[1][1] = m[1][1];
		rm[1][2] = m[2][1];

		rm[2][0] = m[0][2];
		rm[2][1] = m[1][2];
		rm[2][2] = m[2][2];
		return rm;
	}

	FMatrix4 inverse(const FMatrix4& m) {
		const auto pm = (const real* const)(&const_cast<FMatrix4&>(m)[0][0]);

		const auto c00 = pm[10]* pm[15] - pm[14] * pm[11];
		const auto c02 = pm[6] * pm[15] - pm[14] * pm[7];
		const auto c03 = pm[6] * pm[11] - pm[10] * pm[7];
		const auto c04 = pm[9] * pm[15] - pm[13] * pm[11];
		const auto c06 = pm[5] * pm[15] - pm[13] * pm[7];
		const auto c07 = pm[5] * pm[11] - pm[9]  * pm[7];
		const auto c08 = pm[9] * pm[14] - pm[13] * pm[10];
		const auto c10 = pm[5] * pm[14] - pm[13] * pm[6];
		const auto c11 = pm[5] * pm[10] - pm[9]  * pm[6];
		const auto c12 = pm[8] * pm[15] - pm[12] * pm[11];
		const auto c14 = pm[4] * pm[15] - pm[12] * pm[7];
		const auto c15 = pm[4] * pm[11] - pm[8]  * pm[7];
		const auto c16 = pm[8] * pm[14] - pm[12] * pm[10];
		const auto c18 = pm[4] * pm[14] - pm[12] * pm[6];
		const auto c19 = pm[4] * pm[10] - pm[8]  * pm[6];
		const auto c20 = pm[8] * pm[13] - pm[12] * pm[9];
		const auto c22 = pm[4] * pm[13] - pm[12] * pm[5];
		const auto c23 = pm[4] * pm[9]  - pm[8]  * pm[5];

		const FVector4 f0(c00, c00, c02, c03);
		const FVector4 f1(c04, c04, c06, c07);
		const FVector4 f2(c08, c08, c10, c11);
		const FVector4 f3(c12, c12, c14, c15);
		const FVector4 f4(c16, c16, c18, c19);
		const FVector4 f5(c20, c20, c22, c23);

		const FVector4 v0(pm[4], pm[0], pm[0], pm[0]);
		const FVector4 v1(pm[5], pm[1], pm[1], pm[1]);
		const FVector4 v2(pm[6], pm[2], pm[2], pm[2]);
		const FVector4 v3(pm[7], pm[3], pm[3], pm[3]);

		const FVector4 inv0(v1 * f0 - v2 * f1 + v3 * f2);
		const FVector4 inv1(v0 * f0 - v2 * f3 + v3 * f4);
		const FVector4 inv2(v0 * f1 - v1 * f3 + v3 * f5);
		const FVector4 inv3(v0 * f2 - v1 * f4 + v2 * f5);

		const FVector4 signA(+1, -1, +1, -1);
		const FVector4 signB(-1, +1, -1, +1);
		const FMatrix4 res(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		const FVector4 r0(res[0][0], res[1][0], res[2][0], res[3][0]);

		const FVector4 d0(m[0] * r0);
		const auto Dot1 = (d0.x + d0.y) + (d0.z + d0.w);
		const auto OneOverDeterminant = (real)(1) / Dot1;
		return res * OneOverDeterminant;
	}

	FMatrix4 transpose(const FMatrix4& m) {
		FMatrix4 r(1);
		r[0][0] = m[0][0];
		r[0][1] = m[1][0];
		r[0][2] = m[2][0];
		r[0][3] = m[3][0];

		r[1][0] = m[0][1];
		r[1][1] = m[1][1];
		r[1][2] = m[2][1];
		r[1][3] = m[3][1];

		r[2][0] = m[0][2];
		r[2][1] = m[1][2];
		r[2][2] = m[2][2];
		r[2][3] = m[3][2];

		r[3][0] = m[0][3];
		r[3][1] = m[1][3];
		r[3][2] = m[2][3];
		r[3][3] = m[3][3];
		return r;
	}

}
