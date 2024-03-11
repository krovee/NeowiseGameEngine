#include <Math/Math.h>
#include <Math/Packed.h>

namespace Neowise {

	const uint32 CPackUnorm2x16::operator()(const FVector2& v) const {
		union {
			uint16 in[2] = {};
			uint32 out;
		} u;

		u.in[0] = (uint16)(round)(NW_CLAMP(v[0], 0.f, 1.f) * 65535.f);
		u.in[1] = (uint16)(round)(NW_CLAMP(v[1], 0.f, 1.f) * 65535.f);

		return u.out;
	}

	const FVector2 CPackUnorm2x16::operator()(uint32 p) const {
		union {
			uint32 in = {};
			uint16 out[2];
		} u = { p };

		return {
			u.out[0] * 1.5259021896696421759365224689097e-5f,
			u.out[1] * 1.5259021896696421759365224689097e-5f
		};
	}

	const uint32 CPackSnorm2x16::operator()(const FVector2& v) const {
		union {
			int16 in[2] = {};
			uint32 out;
		} u;

		const auto v0 = v[0];
		const auto v1 = v[1];
		u.in[0] = (int16)(round)(NW_CLAMP(v0, -1.f, 1.f) * 32767.f);
		u.in[1] = (int16)(round)(NW_CLAMP(v1, -1.f, 1.f) * 32767.f);

		return u.out;
	}

	const FVector2 CPackSnorm2x16::operator()(uint32 p) const {
		union {
			uint32 in = {};
			int16 out[2];
		} u = { p };

		const real x(u.out[0] * 3.0518509475997192297128208258309e-5f);
		const real y(u.out[1] * 3.0518509475997192297128208258309e-5f);

		return {
			NW_CLAMP(x, -1.f, 1.f),
			NW_CLAMP(y, -1.f, 1.f),
		};

	}

	const uint32 CPackUnorm4x8::operator()(const FVector4& v) const {
		const real* p = &const_cast<FVector4&>(v)[0];

		union {
			uint8 in[4] = {};
			uint32 out;
		} 
		u = {
			(uint8)(round)(NW_CLAMP(p[0], 0.f, 1.f) * 255.f),
			(uint8)(round)(NW_CLAMP(p[1], 0.f, 1.f) * 255.f),
			(uint8)(round)(NW_CLAMP(p[2], 0.f, 1.f) * 255.f),
			(uint8)(round)(NW_CLAMP(p[3], 0.f, 1.f) * 255.f)
		};
		return u.out;
	}

	const FVector4 CPackUnorm4x8::operator()(uint32 p) const {
		union {
			uint32 in = {};
			uint8 out[4];
		} u = { p };

		return {
			u.out[0] * 0.0039215686274509803921568627451f,
			u.out[1] * 0.0039215686274509803921568627451f,
			u.out[2] * 0.0039215686274509803921568627451f,
			u.out[3] * 0.0039215686274509803921568627451f
		};
	}

	const uint32 CPackSnorm4x8::operator()(const FVector4& v) const {
		const real* p = &const_cast<FVector4&>(v)[0];

		union {
			int8 in[4] = {};
			uint32 out;
		}
		u = {
			(int8)(round)(NW_CLAMP(p[0], -1.f, 1.f) * 127.f),
			(int8)(round)(NW_CLAMP(p[1], -1.f, 1.f) * 127.f),
			(int8)(round)(NW_CLAMP(p[2], -1.f, 1.f) * 127.f),
			(int8)(round)(NW_CLAMP(p[3], -1.f, 1.f) * 127.f)
		};
		return u.out;
	}

	const FVector4 CPackSnorm4x8::operator()(uint32 p) const {
		union {
			uint32 in = {};
			int8 out[4];
		} u = { p };

		return {
			NW_CLAMP(u.out[0] * 0.0078740157480315f, -1.f, 1.f),
			NW_CLAMP(u.out[1] * 0.0078740157480315f, -1.f, 1.f),
			NW_CLAMP(u.out[2] * 0.0078740157480315f, -1.f, 1.f),
			NW_CLAMP(u.out[3] * 0.0078740157480315f, -1.f, 1.f)
		};
	}

	const uint32 CPackHalf2x16::operator()(const FVector2& v) const {
		union {
			half in[2] = {};
			uint32 out;
		} u;
		u.in[0] = v[0];
		u.in[1] = v[1];
		return u.out;
	}

	const FVector2 CPackHalf2x16::operator()(uint32 p) const {
		union {
			uint32 in = {};
			half out[2];
		} u = { p };
		return { u.out[0], u.out[1] };
	}

}
