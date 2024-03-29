#pragma once

#include <Base/Common.h>
#include <Math/Math.h>

namespace Neowise {

	enum EPixelFormat {
		E_PIXEL_FORMAT_UNKNOWN,
		E_PIXEL_FORMAT_R8_UNORM,	// R8_UNORM 
		E_PIXEL_FORMAT_RG8_UNORM,	// R8G8_UNORM
		E_PIXEL_FORMAT_RGB8_UNORM,	// R8G8B8_UNORM
		E_PIXEL_FORMAT_RGBA8_UNORM,	// R8G8B8A8_UNORM
		E_PIXEL_FORMAT_BGRA8_UNORM,	// B8G8R8A8_UNORM
		E_PIXEL_FORMAT_R16_UNORM,	// R16_UNORM 
		E_PIXEL_FORMAT_RG16_UNORM,	// R16G16_UNORM
		E_PIXEL_FORMAT_RGB16_UNORM,	// R16G16B16_UNORM
		E_PIXEL_FORMAT_RGBA16_UNORM,// R16G16B16A16_UNORM
		E_PIXEL_FORMAT_BGRA16_UNORM,// B16G16R16A16_UNORM
		E_PIXEL_FORMAT_R32_UNORM,	// R32_UNORM 
		E_PIXEL_FORMAT_RG32_UNORM,	// R32G32_UNORM
		E_PIXEL_FORMAT_RGB32_UNORM,	// R32G32B32_UNORM
		E_PIXEL_FORMAT_RGBA32_UNORM,// R32G32B32A32_UNORM
		E_PIXEL_FORMAT_BGRA32_UNORM,// B32G32R32A32_UNORM
		E_PIXEL_FORMAT_R64_UNORM,	// R64_UNORM 
		E_PIXEL_FORMAT_RG64_UNORM,	// R64G64_UNORM
		E_PIXEL_FORMAT_RGB64_UNORM,	// R64G64B64_UNORM
		E_PIXEL_FORMAT_RGBA64_UNORM,// R64G64B64A64_UNORM
		E_PIXEL_FORMAT_BGRA64_UNORM,// B64G64R64A64_UNORM

		E_PIXEL_FORMAT_ABGR8_UNORM_PACKED32,	// A8B8G8R8_UNORM_PACK_32
		E_PIXEL_FORMAT_A2BGR10_UNORM_PACKED32,	// A2B10G10R10_UNORM_PACK_32
		E_PIXEL_FORMAT_A2RGB10_UNORM_PACKED32,	// A2R10G10B10_UNORM_PACK_32

		E_PIXEL_FORMAT_R16_FLOAT,		// R16_SFLOAT
		E_PIXEL_FORMAT_RG16_FLOAT,		// R16G16_SFLOAT
		E_PIXEL_FORMAT_RGB16_FLOAT,		// R16G16B16_SFLOAT
		E_PIXEL_FORMAT_RGBA16_FLOAT,	// R16G16B16A16_SFLOAT
		E_PIXEL_FORMAT_R32_FLOAT,		// R32_SFLOAT
		E_PIXEL_FORMAT_RG32_FLOAT,		// R32G32_SFLOAT
		E_PIXEL_FORMAT_RGB32_FLOAT,		// R32G32B32_SFLOAT
		E_PIXEL_FORMAT_RGBA32_FLOAT,	// R32G32B32A32_SFLOAT
		E_PIXEL_FORMAT_R64_FLOAT,		// R64_SFLOAT
		E_PIXEL_FORMAT_RG64_FLOAT,		// R64G64_SFLOAT
		E_PIXEL_FORMAT_RGB64_FLOAT,		// R64G64B64_SFLOAT
		E_PIXEL_FORMAT_RGBA64_FLOAT,	// R64G64B64A64_SFLOAT

		E_PIXEL_FORMAT_B10GR11U_FLOAT_PACKED32,	// B10G11R11_UFLOAT_PACK32
		E_PIXEL_FORMAT_D16_UNORM,		// D16_UNORM
		E_PIXEL_FORMAT_D32_FLOAT,		// D32_SFLOAT

		E_PIXEL_FORMAT_N_COUNT
	};

	enum EBufferingState {
		E_BUFFERING_STATE_DOUBLE_BUFFER,
		E_BUFFERING_STATE_TRIPPLE_BUFFER,

		E_BUFFERING_STATE_N_COUNT
	};

}