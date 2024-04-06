#pragma once

#include <Base/NumericTypes.h>
#include <Input/Keycode.h>

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

#ifndef __stdcall
#	define __stdcall
#endif

namespace Neowise::Platform::Windows {
	using HANDLE	= void*;
	using LPVOID	= void*;
	using CLPVOID	= const void*;
	using BOOL		= int32;
	struct HWND__ { int unused; };
	struct HINSTANCE__ { int unused; };
	using HWND		= HWND__*;
	using HINSTANCE	= HINSTANCE__*;
	using UINT		= uint64;
	using WPARAM	= uint64;
	using LPARAM	= uint64;
	using DWORD		= unsigned long;
	using CHAR		= char;
	using BYTE		= char;
	using LONG		= long;
	using WORD		= uint16;
	using COLORREF	= DWORD;
	using INT_PTR	= long long;
	struct RECT {
		LONG    left;
		LONG    top;
		LONG    right;
		LONG    bottom;
	};

	struct PIXELFORMATDESCRIPTOR {
		WORD  nSize;
		WORD  nVersion;
		DWORD dwFlags;
		BYTE  iPixelType;
		BYTE  cColorBits;
		BYTE  cRedBits;
		BYTE  cRedShift;
		BYTE  cGreenBits;
		BYTE  cGreenShift;
		BYTE  cBlueBits;
		BYTE  cBlueShift;
		BYTE  cAlphaBits;
		BYTE  cAlphaShift;
		BYTE  cAccumBits;
		BYTE  cAccumRedBits;
		BYTE  cAccumGreenBits;
		BYTE  cAccumBlueBits;
		BYTE  cAccumAlphaBits;
		BYTE  cDepthBits;
		BYTE  cStencilBits;
		BYTE  cAuxBuffers;
		BYTE  iLayerType;
		BYTE  bReserved;
		DWORD dwLayerMask;
		DWORD dwVisibleMask;
		DWORD dwDamageMask;
	};

	struct LAYERPLANEDESCRIPTOR {
		WORD  nSize;
		WORD  nVersion;
		DWORD dwFlags;
		BYTE  iPixelType;
		BYTE  cColorBits;
		BYTE  cRedBits;
		BYTE  cRedShift;
		BYTE  cGreenBits;
		BYTE  cGreenShift;
		BYTE  cBlueBits;
		BYTE  cBlueShift;
		BYTE  cAlphaBits;
		BYTE  cAlphaShift;
		BYTE  cAccumBits;
		BYTE  cAccumRedBits;
		BYTE  cAccumGreenBits;
		BYTE  cAccumBlueBits;
		BYTE  cAccumAlphaBits;
		BYTE  cDepthBits;
		BYTE  cStencilBits;
		BYTE  cAuxBuffers;
		BYTE  iLayerPlane;
		BYTE  bReserved;
		COLORREF crTransparent;
	};

	struct POINTFLOAT  {
		float   x;
		float   y;
	};

	struct GLYPHMETRICSFLOAT {
		float		gmfBlackBoxX;
		float		gmfBlackBoxY;
		POINTFLOAT  gmfptGlyphOrigin;
		float       gmfCellIncX;
		float       gmfCellIncY;
	};

	struct _GPU_DEVICE {
		DWORD  cb;
		CHAR   DeviceName[32];
		CHAR   DeviceString[128];
		DWORD  Flags;
		RECT   rcVirtualScreen;
	};

	DECLARE_HANDLE(HPBUFFERARB);
	DECLARE_HANDLE(HPBUFFEREXT);
	DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
	DECLARE_HANDLE(HPVIDEODEV);
	DECLARE_HANDLE(HPGPUNV);
	DECLARE_HANDLE(HGPUNV);
	DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
	DECLARE_HANDLE(HGLRC);
	DECLARE_HANDLE(HDESK);
	DECLARE_HANDLE(HDC);
	DECLARE_HANDLE(HENHMETAFILE);
	typedef struct _GPU_DEVICE GPU_DEVICE;
	typedef struct _GPU_DEVICE* PGPU_DEVICE;
	typedef INT_PTR(__stdcall* PROC)();


#define WGL_VERSION_1_0 1
	extern int GLAD_WGL_VERSION_1_0;
#define WGL_3DFX_multisample 1
	extern int GLAD_WGL_3DFX_multisample;
#define WGL_3DL_stereo_control 1
	extern int GLAD_WGL_3DL_stereo_control;
#define WGL_AMD_gpu_association 1
	extern int GLAD_WGL_AMD_gpu_association;
#define WGL_ARB_buffer_region 1
	extern int GLAD_WGL_ARB_buffer_region;
#define WGL_ARB_context_flush_control 1
	extern int GLAD_WGL_ARB_context_flush_control;
#define WGL_ARB_create_context 1
	extern int GLAD_WGL_ARB_create_context;
#define WGL_ARB_create_context_no_error 1
	extern int GLAD_WGL_ARB_create_context_no_error;
#define WGL_ARB_create_context_profile 1
	extern int GLAD_WGL_ARB_create_context_profile;
#define WGL_ARB_create_context_robustness 1
	extern int GLAD_WGL_ARB_create_context_robustness;
#define WGL_ARB_extensions_string 1
	extern int GLAD_WGL_ARB_extensions_string;
#define WGL_ARB_framebuffer_sRGB 1
	extern int GLAD_WGL_ARB_framebuffer_sRGB;
#define WGL_ARB_make_current_read 1
	extern int GLAD_WGL_ARB_make_current_read;
#define WGL_ARB_multisample 1
	extern int GLAD_WGL_ARB_multisample;
#define WGL_ARB_pbuffer 1
	extern int GLAD_WGL_ARB_pbuffer;
#define WGL_ARB_pixel_format 1
	extern int GLAD_WGL_ARB_pixel_format;
#define WGL_ARB_pixel_format_float 1
	extern int GLAD_WGL_ARB_pixel_format_float;
#define WGL_ARB_render_texture 1
	extern int GLAD_WGL_ARB_render_texture;
#define WGL_ARB_robustness_application_isolation 1
	extern int GLAD_WGL_ARB_robustness_application_isolation;
#define WGL_ARB_robustness_share_group_isolation 1
	extern int GLAD_WGL_ARB_robustness_share_group_isolation;
#define WGL_ATI_pixel_format_float 1
	extern int GLAD_WGL_ATI_pixel_format_float;
#define WGL_ATI_render_texture_rectangle 1
	extern int GLAD_WGL_ATI_render_texture_rectangle;
#define WGL_EXT_colorspace 1
	extern int GLAD_WGL_EXT_colorspace;
#define WGL_EXT_create_context_es2_profile 1
	extern int GLAD_WGL_EXT_create_context_es2_profile;
#define WGL_EXT_create_context_es_profile 1
	extern int GLAD_WGL_EXT_create_context_es_profile;
#define WGL_EXT_depth_float 1
	extern int GLAD_WGL_EXT_depth_float;
#define WGL_EXT_display_color_table 1
	extern int GLAD_WGL_EXT_display_color_table;
#define WGL_EXT_extensions_string 1
	extern int GLAD_WGL_EXT_extensions_string;
#define WGL_EXT_framebuffer_sRGB 1
	extern int GLAD_WGL_EXT_framebuffer_sRGB;
#define WGL_EXT_make_current_read 1
	extern int GLAD_WGL_EXT_make_current_read;
#define WGL_EXT_multisample 1
	extern int GLAD_WGL_EXT_multisample;
#define WGL_EXT_pbuffer 1
	extern int GLAD_WGL_EXT_pbuffer;
#define WGL_EXT_pixel_format 1
	extern int GLAD_WGL_EXT_pixel_format;
#define WGL_EXT_pixel_format_packed_float 1
	extern int GLAD_WGL_EXT_pixel_format_packed_float;
#define WGL_EXT_swap_control 1
	extern int GLAD_WGL_EXT_swap_control;
#define WGL_EXT_swap_control_tear 1
	extern int GLAD_WGL_EXT_swap_control_tear;
#define WGL_I3D_digital_video_control 1
	extern int GLAD_WGL_I3D_digital_video_control;
#define WGL_I3D_gamma 1
	extern int GLAD_WGL_I3D_gamma;
#define WGL_I3D_genlock 1
	extern int GLAD_WGL_I3D_genlock;
#define WGL_I3D_image_buffer 1
	extern int GLAD_WGL_I3D_image_buffer;
#define WGL_I3D_swap_frame_lock 1
	extern int GLAD_WGL_I3D_swap_frame_lock;
#define WGL_I3D_swap_frame_usage 1
	extern int GLAD_WGL_I3D_swap_frame_usage;
#define WGL_NV_DX_interop 1
	extern int GLAD_WGL_NV_DX_interop;
#define WGL_NV_DX_interop2 1
	extern int GLAD_WGL_NV_DX_interop2;
#define WGL_NV_copy_image 1
	extern int GLAD_WGL_NV_copy_image;
#define WGL_NV_delay_before_swap 1
	extern int GLAD_WGL_NV_delay_before_swap;
#define WGL_NV_float_buffer 1
	extern int GLAD_WGL_NV_float_buffer;
#define WGL_NV_gpu_affinity 1
	extern int GLAD_WGL_NV_gpu_affinity;
#define WGL_NV_multigpu_context 1
	extern int GLAD_WGL_NV_multigpu_context;
#define WGL_NV_multisample_coverage 1
	extern int GLAD_WGL_NV_multisample_coverage;
#define WGL_NV_present_video 1
	extern int GLAD_WGL_NV_present_video;
#define WGL_NV_render_depth_texture 1
	extern int GLAD_WGL_NV_render_depth_texture;
#define WGL_NV_render_texture_rectangle 1
	extern int GLAD_WGL_NV_render_texture_rectangle;
#define WGL_NV_swap_group 1
	extern int GLAD_WGL_NV_swap_group;
#define WGL_NV_vertex_array_range 1
	extern int GLAD_WGL_NV_vertex_array_range;
#define WGL_NV_video_capture 1
	extern int GLAD_WGL_NV_video_capture;
#define WGL_NV_video_output 1
	extern int GLAD_WGL_NV_video_output;
#define WGL_OML_sync_control 1
	extern int GLAD_WGL_OML_sync_control;


#ifdef WGL_FONT_LINES
#	undef WGL_FONT_LINES
#endif 

#ifdef WGL_FONT_POLYGONS
#	undef WGL_FONT_POLYGONS
#endif 

#ifdef WGL_SWAP_MAIN_PLANE
#	undef WGL_SWAP_MAIN_PLANE
#endif 

#ifdef WGL_SWAP_OVERLAY1
#	undef WGL_SWAP_OVERLAY1
#endif 

#ifdef WGL_SWAP_OVERLAY10
#	undef WGL_SWAP_OVERLAY10
#endif 

#ifdef WGL_SWAP_OVERLAY11
#	undef WGL_SWAP_OVERLAY11
#endif 

#ifdef WGL_SWAP_OVERLAY12
#	undef WGL_SWAP_OVERLAY12
#endif 

#ifdef WGL_SWAP_OVERLAY13
#	undef WGL_SWAP_OVERLAY13
#endif 

#ifdef WGL_SWAP_OVERLAY14
#	undef WGL_SWAP_OVERLAY14
#endif 

#ifdef WGL_SWAP_OVERLAY15
#	undef WGL_SWAP_OVERLAY15
#endif 

#ifdef WGL_SWAP_OVERLAY2
#	undef WGL_SWAP_OVERLAY2
#endif 

#ifdef WGL_SWAP_OVERLAY3
#	undef WGL_SWAP_OVERLAY3
#endif 

#ifdef WGL_SWAP_OVERLAY4
#	undef WGL_SWAP_OVERLAY4
#endif 

#ifdef WGL_SWAP_OVERLAY5
#	undef WGL_SWAP_OVERLAY5
#endif 

#ifdef WGL_SWAP_OVERLAY6
#	undef WGL_SWAP_OVERLAY6
#endif 

#ifdef WGL_SWAP_OVERLAY7
#	undef WGL_SWAP_OVERLAY7
#endif 

#ifdef WGL_SWAP_OVERLAY8
#	undef WGL_SWAP_OVERLAY8
#endif 

#ifdef WGL_SWAP_OVERLAY9
#	undef WGL_SWAP_OVERLAY9
#endif 

#ifdef WGL_SWAP_UNDERLAY1
#	undef WGL_SWAP_UNDERLAY1
#endif 

#ifdef WGL_SWAP_UNDERLAY10
#	undef WGL_SWAP_UNDERLAY10
#endif 

#ifdef WGL_SWAP_UNDERLAY11
#	undef WGL_SWAP_UNDERLAY11
#endif 

#ifdef WGL_SWAP_UNDERLAY12
#	undef WGL_SWAP_UNDERLAY12
#endif 

#ifdef WGL_SWAP_UNDERLAY13
#	undef WGL_SWAP_UNDERLAY13
#endif 

#ifdef WGL_SWAP_UNDERLAY14
#	undef WGL_SWAP_UNDERLAY14
#endif 

#ifdef WGL_SWAP_UNDERLAY15
#	undef WGL_SWAP_UNDERLAY15
#endif 

#ifdef WGL_SWAP_UNDERLAY2
#	undef WGL_SWAP_UNDERLAY2
#endif 

#ifdef WGL_SWAP_UNDERLAY3
#	undef WGL_SWAP_UNDERLAY3
#endif 

#ifdef WGL_SWAP_UNDERLAY4
#	undef WGL_SWAP_UNDERLAY4
#endif 

#ifdef WGL_SWAP_UNDERLAY5
#	undef WGL_SWAP_UNDERLAY5
#endif 

#ifdef WGL_SWAP_UNDERLAY6
#	undef WGL_SWAP_UNDERLAY6
#endif 

#ifdef WGL_SWAP_UNDERLAY7
#	undef WGL_SWAP_UNDERLAY7
#endif 

#ifdef WGL_SWAP_UNDERLAY8
#	undef WGL_SWAP_UNDERLAY8
#endif 

#ifdef WGL_SWAP_UNDERLAY9
#	undef WGL_SWAP_UNDERLAY9
#endif 


	enum {
		ERROR_INCOMPATIBLE_AFFINITY_MASKS_NV = 0x20D0,
		ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB = 0x2054,
		ERROR_INVALID_PIXEL_TYPE_ARB = 0x2043,
		ERROR_INVALID_PIXEL_TYPE_EXT = 0x2043,
		ERROR_INVALID_PROFILE_ARB = 0x2096,
		ERROR_INVALID_VERSION_ARB = 0x2095,
		ERROR_MISSING_AFFINITY_MASK_NV = 0x20D1,
		WGL_ACCELERATION_ARB = 0x2003,
		WGL_ACCELERATION_EXT = 0x2003,
		WGL_ACCESS_READ_ONLY_NV = 0x00000000,
		WGL_ACCESS_READ_WRITE_NV = 0x00000001,
		WGL_ACCESS_WRITE_DISCARD_NV = 0x00000002,
		WGL_ACCUM_ALPHA_BITS_ARB = 0x2021,
		WGL_ACCUM_ALPHA_BITS_EXT = 0x2021,
		WGL_ACCUM_BITS_ARB = 0x201D,
		WGL_ACCUM_BITS_EXT = 0x201D,
		WGL_ACCUM_BLUE_BITS_ARB = 0x2020,
		WGL_ACCUM_BLUE_BITS_EXT = 0x2020,
		WGL_ACCUM_GREEN_BITS_ARB = 0x201F,
		WGL_ACCUM_GREEN_BITS_EXT = 0x201F,
		WGL_ACCUM_RED_BITS_ARB = 0x201E,
		WGL_ACCUM_RED_BITS_EXT = 0x201E,
		WGL_ALPHA_BITS_ARB = 0x201B,
		WGL_ALPHA_BITS_EXT = 0x201B,
		WGL_ALPHA_SHIFT_ARB = 0x201C,
		WGL_ALPHA_SHIFT_EXT = 0x201C,
		WGL_AUX0_ARB = 0x2087,
		WGL_AUX1_ARB = 0x2088,
		WGL_AUX2_ARB = 0x2089,
		WGL_AUX3_ARB = 0x208A,
		WGL_AUX4_ARB = 0x208B,
		WGL_AUX5_ARB = 0x208C,
		WGL_AUX6_ARB = 0x208D,
		WGL_AUX7_ARB = 0x208E,
		WGL_AUX8_ARB = 0x208F,
		WGL_AUX9_ARB = 0x2090,
		WGL_AUX_BUFFERS_ARB = 0x2024,
		WGL_AUX_BUFFERS_EXT = 0x2024,
		WGL_BACK_COLOR_BUFFER_BIT_ARB = 0x00000002,
		WGL_BACK_LEFT_ARB = 0x2085,
		WGL_BACK_RIGHT_ARB = 0x2086,
		WGL_BIND_TO_TEXTURE_DEPTH_NV = 0x20A3,
		WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV = 0x20A4,
		WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV = 0x20B4,
		WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV = 0x20B3,
		WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV = 0x20B2,
		WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV = 0x20B1,
		WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV = 0x20A1,
		WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV = 0x20A0,
		WGL_BIND_TO_TEXTURE_RGBA_ARB = 0x2071,
		WGL_BIND_TO_TEXTURE_RGB_ARB = 0x2070,
		WGL_BIND_TO_VIDEO_RGBA_NV = 0x20C1,
		WGL_BIND_TO_VIDEO_RGB_AND_DEPTH_NV = 0x20C2,
		WGL_BIND_TO_VIDEO_RGB_NV = 0x20C0,
		WGL_BLUE_BITS_ARB = 0x2019,
		WGL_BLUE_BITS_EXT = 0x2019,
		WGL_BLUE_SHIFT_ARB = 0x201A,
		WGL_BLUE_SHIFT_EXT = 0x201A,
		WGL_COLORSPACE_EXT = 0x309D,
		WGL_COLORSPACE_LINEAR_EXT = 0x308A,
		WGL_COLORSPACE_SRGB_EXT = 0x3089,
		WGL_COLOR_BITS_ARB = 0x2014,
		WGL_COLOR_BITS_EXT = 0x2014,
		WGL_COLOR_SAMPLES_NV = 0x20B9,
		WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x00000002,
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001,
		WGL_CONTEXT_DEBUG_BIT_ARB = 0x00000001,
		WGL_CONTEXT_ES2_PROFILE_BIT_EXT = 0x00000004,
		WGL_CONTEXT_ES_PROFILE_BIT_EXT = 0x00000004,
		WGL_CONTEXT_FLAGS_ARB = 0x2094,
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x00000002,
		WGL_CONTEXT_LAYER_PLANE_ARB = 0x2093,
		WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091,
		WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092,
		WGL_CONTEXT_MULTIGPU_ATTRIB_AFR_NV = 0x20AC,
		WGL_CONTEXT_MULTIGPU_ATTRIB_MULTICAST_NV = 0x20AD,
		WGL_CONTEXT_MULTIGPU_ATTRIB_MULTI_DISPLAY_MULTICAST_NV = 0x20AE,
		WGL_CONTEXT_MULTIGPU_ATTRIB_NV = 0x20AA,
		WGL_CONTEXT_MULTIGPU_ATTRIB_SINGLE_NV = 0x20AB,
		WGL_CONTEXT_OPENGL_NO_ERROR_ARB = 0x31B3,
		WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126,
		WGL_CONTEXT_RELEASE_BEHAVIOR_ARB = 0x2097,
		WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB = 0x2098,
		WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB = 0,
		WGL_CONTEXT_RESET_ISOLATION_BIT_ARB = 0x00000008,
		WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB = 0x8256,
		WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB = 0x00000004,
		WGL_COVERAGE_SAMPLES_NV = 0x2042,
		WGL_CUBE_MAP_FACE_ARB = 0x207C,
		WGL_DEPTH_BITS_ARB = 0x2022,
		WGL_DEPTH_BITS_EXT = 0x2022,
		WGL_DEPTH_BUFFER_BIT_ARB = 0x00000004,
		WGL_DEPTH_COMPONENT_NV = 0x20A7,
		WGL_DEPTH_FLOAT_EXT = 0x2040,
		WGL_DEPTH_TEXTURE_FORMAT_NV = 0x20A5,
		WGL_DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D = 0x2050,
		WGL_DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D = 0x2051,
		WGL_DIGITAL_VIDEO_CURSOR_INCLUDED_I3D = 0x2052,
		WGL_DIGITAL_VIDEO_GAMMA_CORRECTED_I3D = 0x2053,
		WGL_DOUBLE_BUFFER_ARB = 0x2011,
		WGL_DOUBLE_BUFFER_EXT = 0x2011,
		WGL_DRAW_TO_BITMAP_ARB = 0x2002,
		WGL_DRAW_TO_BITMAP_EXT = 0x2002,
		WGL_DRAW_TO_PBUFFER_ARB = 0x202D,
		WGL_DRAW_TO_PBUFFER_EXT = 0x202D,
		WGL_DRAW_TO_WINDOW_ARB = 0x2001,
		WGL_DRAW_TO_WINDOW_EXT = 0x2001,
		WGL_FLOAT_COMPONENTS_NV = 0x20B0,
	};

	enum : uint {
		WGL_FONT_LINES = 0,
		WGL_FONT_POLYGONS = 1,
		WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB = 0x20A9,
		WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT = 0x20A9,
		WGL_FRONT_COLOR_BUFFER_BIT_ARB = 0x00000001,
		WGL_FRONT_LEFT_ARB = 0x2083,
		WGL_FRONT_RIGHT_ARB = 0x2084,
		WGL_FULL_ACCELERATION_ARB = 0x2027,
		WGL_FULL_ACCELERATION_EXT = 0x2027,
		WGL_GAMMA_EXCLUDE_DESKTOP_I3D = 0x204F,
		WGL_GAMMA_TABLE_SIZE_I3D = 0x204E,
		WGL_GENERIC_ACCELERATION_ARB = 0x2026,
		WGL_GENERIC_ACCELERATION_EXT = 0x2026,
		WGL_GENLOCK_SOURCE_DIGITAL_FIELD_I3D = 0x2049,
		WGL_GENLOCK_SOURCE_DIGITAL_SYNC_I3D = 0x2048,
		WGL_GENLOCK_SOURCE_EDGE_BOTH_I3D = 0x204C,
		WGL_GENLOCK_SOURCE_EDGE_FALLING_I3D = 0x204A,
		WGL_GENLOCK_SOURCE_EDGE_RISING_I3D = 0x204B,
		WGL_GENLOCK_SOURCE_EXTERNAL_FIELD_I3D = 0x2046,
		WGL_GENLOCK_SOURCE_EXTERNAL_SYNC_I3D = 0x2045,
		WGL_GENLOCK_SOURCE_EXTERNAL_TTL_I3D = 0x2047,
		WGL_GENLOCK_SOURCE_MULTIVIEW_I3D = 0x2044,
		WGL_GPU_CLOCK_AMD = 0x21A4,
		WGL_GPU_FASTEST_TARGET_GPUS_AMD = 0x21A2,
		WGL_GPU_NUM_PIPES_AMD = 0x21A5,
		WGL_GPU_NUM_RB_AMD = 0x21A7,
		WGL_GPU_NUM_SIMD_AMD = 0x21A6,
		WGL_GPU_NUM_SPI_AMD = 0x21A8,
		WGL_GPU_OPENGL_VERSION_STRING_AMD = 0x1F02,
		WGL_GPU_RAM_AMD = 0x21A3,
		WGL_GPU_RENDERER_STRING_AMD = 0x1F01,
		WGL_GPU_VENDOR_AMD = 0x1F00,
		WGL_GREEN_BITS_ARB = 0x2017,
		WGL_GREEN_BITS_EXT = 0x2017,
		WGL_GREEN_SHIFT_ARB = 0x2018,
		WGL_GREEN_SHIFT_EXT = 0x2018,
		WGL_IMAGE_BUFFER_LOCK_I3D = 0x00000002,
		WGL_IMAGE_BUFFER_MIN_ACCESS_I3D = 0x00000001,
		WGL_LOSE_CONTEXT_ON_RESET_ARB = 0x8252,
		WGL_MAX_PBUFFER_HEIGHT_ARB = 0x2030,
		WGL_MAX_PBUFFER_HEIGHT_EXT = 0x2030,
		WGL_MAX_PBUFFER_PIXELS_ARB = 0x202E,
		WGL_MAX_PBUFFER_PIXELS_EXT = 0x202E,
		WGL_MAX_PBUFFER_WIDTH_ARB = 0x202F,
		WGL_MAX_PBUFFER_WIDTH_EXT = 0x202F,
		WGL_MIPMAP_LEVEL_ARB = 0x207B,
		WGL_MIPMAP_TEXTURE_ARB = 0x2074,
		WGL_NEED_PALETTE_ARB = 0x2004,
		WGL_NEED_PALETTE_EXT = 0x2004,
		WGL_NEED_SYSTEM_PALETTE_ARB = 0x2005,
		WGL_NEED_SYSTEM_PALETTE_EXT = 0x2005,
		WGL_NO_ACCELERATION_ARB = 0x2025,
		WGL_NO_ACCELERATION_EXT = 0x2025,
		WGL_NO_RESET_NOTIFICATION_ARB = 0x8261,
		WGL_NO_TEXTURE_ARB = 0x2077,
		WGL_NUMBER_OVERLAYS_ARB = 0x2008,
		WGL_NUMBER_OVERLAYS_EXT = 0x2008,
		WGL_NUMBER_PIXEL_FORMATS_ARB = 0x2000,
		WGL_NUMBER_PIXEL_FORMATS_EXT = 0x2000,
		WGL_NUMBER_UNDERLAYS_ARB = 0x2009,
		WGL_NUMBER_UNDERLAYS_EXT = 0x2009,
		WGL_NUM_VIDEO_CAPTURE_SLOTS_NV = 0x20CF,
		WGL_NUM_VIDEO_SLOTS_NV = 0x20F0,
		WGL_OPTIMAL_PBUFFER_HEIGHT_EXT = 0x2032,
		WGL_OPTIMAL_PBUFFER_WIDTH_EXT = 0x2031,
		WGL_PBUFFER_HEIGHT_ARB = 0x2035,
		WGL_PBUFFER_HEIGHT_EXT = 0x2035,
		WGL_PBUFFER_LARGEST_ARB = 0x2033,
		WGL_PBUFFER_LARGEST_EXT = 0x2033,
		WGL_PBUFFER_LOST_ARB = 0x2036,
		WGL_PBUFFER_WIDTH_ARB = 0x2034,
		WGL_PBUFFER_WIDTH_EXT = 0x2034,
		WGL_PIXEL_TYPE_ARB = 0x2013,
		WGL_PIXEL_TYPE_EXT = 0x2013,
		WGL_RED_BITS_ARB = 0x2015,
		WGL_RED_BITS_EXT = 0x2015,
		WGL_RED_SHIFT_ARB = 0x2016,
		WGL_RED_SHIFT_EXT = 0x2016,
		WGL_SAMPLES_3DFX = 0x2061,
		WGL_SAMPLES_ARB = 0x2042,
		WGL_SAMPLES_EXT = 0x2042,
		WGL_SAMPLE_BUFFERS_3DFX = 0x2060,
		WGL_SAMPLE_BUFFERS_ARB = 0x2041,
		WGL_SAMPLE_BUFFERS_EXT = 0x2041,
		WGL_SHARE_ACCUM_ARB = 0x200E,
		WGL_SHARE_ACCUM_EXT = 0x200E,
		WGL_SHARE_DEPTH_ARB = 0x200C,
		WGL_SHARE_DEPTH_EXT = 0x200C,
		WGL_SHARE_STENCIL_ARB = 0x200D,
		WGL_SHARE_STENCIL_EXT = 0x200D,
		WGL_STENCIL_BITS_ARB = 0x2023,
		WGL_STENCIL_BITS_EXT = 0x2023,
		WGL_STENCIL_BUFFER_BIT_ARB = 0x00000008,
		WGL_STEREO_ARB = 0x2012,
		WGL_STEREO_EMITTER_DISABLE_3DL = 0x2056,
		WGL_STEREO_EMITTER_ENABLE_3DL = 0x2055,
		WGL_STEREO_EXT = 0x2012,
		WGL_STEREO_POLARITY_INVERT_3DL = 0x2058,
		WGL_STEREO_POLARITY_NORMAL_3DL = 0x2057,
		WGL_SUPPORT_GDI_ARB = 0x200F,
		WGL_SUPPORT_GDI_EXT = 0x200F,
		WGL_SUPPORT_OPENGL_ARB = 0x2010,
		WGL_SUPPORT_OPENGL_EXT = 0x2010,
		WGL_SWAP_COPY_ARB = 0x2029,
		WGL_SWAP_COPY_EXT = 0x2029,
		WGL_SWAP_EXCHANGE_ARB = 0x2028,
		WGL_SWAP_EXCHANGE_EXT = 0x2028,
		WGL_SWAP_LAYER_BUFFERS_ARB = 0x2006,
		WGL_SWAP_LAYER_BUFFERS_EXT = 0x2006,
		WGL_SWAP_MAIN_PLANE = 0x00000001,
		WGL_SWAP_METHOD_ARB = 0x2007,
		WGL_SWAP_METHOD_EXT = 0x2007,
		WGL_SWAP_OVERLAY1 = 0x00000002,
		WGL_SWAP_OVERLAY10 = 0x00000400,
		WGL_SWAP_OVERLAY11 = 0x00000800,
		WGL_SWAP_OVERLAY12 = 0x00001000,
		WGL_SWAP_OVERLAY13 = 0x00002000,
		WGL_SWAP_OVERLAY14 = 0x00004000,
		WGL_SWAP_OVERLAY15 = 0x00008000,
		WGL_SWAP_OVERLAY2 = 0x00000004,
		WGL_SWAP_OVERLAY3 = 0x00000008,
		WGL_SWAP_OVERLAY4 = 0x00000010,
		WGL_SWAP_OVERLAY5 = 0x00000020,
		WGL_SWAP_OVERLAY6 = 0x00000040,
		WGL_SWAP_OVERLAY7 = 0x00000080,
		WGL_SWAP_OVERLAY8 = 0x00000100,
		WGL_SWAP_OVERLAY9 = 0x00000200,
		WGL_SWAP_UNDEFINED_ARB = 0x202A,
		WGL_SWAP_UNDEFINED_EXT = 0x202A,
		WGL_SWAP_UNDERLAY1 = 0x00010000,
		WGL_SWAP_UNDERLAY10 = 0x02000000,
		WGL_SWAP_UNDERLAY11 = 0x04000000,
		WGL_SWAP_UNDERLAY12 = 0x08000000,
		WGL_SWAP_UNDERLAY13 = 0x10000000,
		WGL_SWAP_UNDERLAY14 = 0x20000000,
		WGL_SWAP_UNDERLAY15 = 0x40000000,
		WGL_SWAP_UNDERLAY2 = 0x00020000,
		WGL_SWAP_UNDERLAY3 = 0x00040000,
		WGL_SWAP_UNDERLAY4 = 0x00080000,
		WGL_SWAP_UNDERLAY5 = 0x00100000,
		WGL_SWAP_UNDERLAY6 = 0x00200000,
		WGL_SWAP_UNDERLAY7 = 0x00400000,
		WGL_SWAP_UNDERLAY8 = 0x00800000,
		WGL_SWAP_UNDERLAY9 = 0x01000000,
		WGL_TEXTURE_1D_ARB = 0x2079,
		WGL_TEXTURE_2D_ARB = 0x207A,
		WGL_TEXTURE_CUBE_MAP_ARB = 0x2078,
		WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB = 0x207E,
		WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB = 0x2080,
		WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB = 0x2082,
		WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB = 0x207D,
		WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB = 0x207F,
		WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB = 0x2081,
		WGL_TEXTURE_DEPTH_COMPONENT_NV = 0x20A6,
		WGL_TEXTURE_FLOAT_RGBA_NV = 0x20B8,
		WGL_TEXTURE_FLOAT_RGB_NV = 0x20B7,
		WGL_TEXTURE_FLOAT_RG_NV = 0x20B6,
		WGL_TEXTURE_FLOAT_R_NV = 0x20B5,
		WGL_TEXTURE_FORMAT_ARB = 0x2072,
		WGL_TEXTURE_RECTANGLE_ATI = 0x21A5,
		WGL_TEXTURE_RECTANGLE_NV = 0x20A2,
		WGL_TEXTURE_RGBA_ARB = 0x2076,
		WGL_TEXTURE_RGB_ARB = 0x2075,
		WGL_TEXTURE_TARGET_ARB = 0x2073,
		WGL_TRANSPARENT_ALPHA_VALUE_ARB = 0x203A,
		WGL_TRANSPARENT_ARB = 0x200A,
		WGL_TRANSPARENT_BLUE_VALUE_ARB = 0x2039,
		WGL_TRANSPARENT_EXT = 0x200A,
		WGL_TRANSPARENT_GREEN_VALUE_ARB = 0x2038,
		WGL_TRANSPARENT_INDEX_VALUE_ARB = 0x203B,
		WGL_TRANSPARENT_RED_VALUE_ARB = 0x2037,
		WGL_TRANSPARENT_VALUE_EXT = 0x200B,
		WGL_TYPE_COLORINDEX_ARB = 0x202C,
		WGL_TYPE_COLORINDEX_EXT = 0x202C,
		WGL_TYPE_RGBA_ARB = 0x202B,
		WGL_TYPE_RGBA_EXT = 0x202B,
		WGL_TYPE_RGBA_FLOAT_ARB = 0x21A0,
		WGL_TYPE_RGBA_FLOAT_ATI = 0x21A0,
		WGL_TYPE_RGBA_UNSIGNED_FLOAT_EXT = 0x20A8,
		WGL_UNIQUE_ID_NV = 0x20CE,
		WGL_VIDEO_OUT_ALPHA_NV = 0x20C4,
		WGL_VIDEO_OUT_COLOR_AND_ALPHA_NV = 0x20C6,
		WGL_VIDEO_OUT_COLOR_AND_DEPTH_NV = 0x20C7,
		WGL_VIDEO_OUT_COLOR_NV = 0x20C3,
		WGL_VIDEO_OUT_DEPTH_NV = 0x20C5,
		WGL_VIDEO_OUT_FIELD_1 = 0x20C9,
		WGL_VIDEO_OUT_FIELD_2 = 0x20CA,
		WGL_VIDEO_OUT_FRAME = 0x20C8,
		WGL_VIDEO_OUT_STACKED_FIELDS_1_2 = 0x20CB,
		WGL_VIDEO_OUT_STACKED_FIELDS_2_1 = 0x20CC,
	};

	enum { THREAD_HANDLE_INVALID = 0xffffffff };

	enum HeapAllocFlags {
		E_HEAP_ALLOC_FLAGS_UNDEFINED,
		E_HEAP_ALLOC_FLAGS_ZERO_INITIALIZED,
	};

	enum WindowFlags : uint64 {
		E_WINDOW_FLAGS_DEFAULT		= 13565952,
		E_WINDOW_FLAGS_BORDERLESS	= 2148466688
	};

	enum WindowShowFlags {
		E_WINDOW_SHOW_FLAGS_NORMAL = 5,
		E_WINDOW_SHOW_FLAGS_HIDDEN = 6,
		E_WINDOW_SHOW_FLAGS_MAXIMIZED = 3,
	};

	enum WindowLongPtrName {
		E_WINDOW_LONG_PTR_NAME_STYLE = -16,
		E_WINDOW_LONG_PTR_NAME_USERDATA = -21
	};

	enum EVirtualKey : uint8 {
		E_VK_LBUTTON = 1,
		E_VK_RBUTTON = 2,
		E_VK_CANCEL = 3,
		E_VK_MBUTTON = 4,
		E_VK_XBUTTON1 = 5,
		E_VK_XBUTTON2 = 6,
		/////////////////
		E_VK_BACKSPACE = 8,
		E_VK_TAB = 9,
		/////////////////
		E_VK_CLEAR = 12,
		E_VK_ENTER = 13,
		/////////////////
		E_VK_SHIFT = 16,
		E_VK_CONTROL = 17,
		E_VK_ALT = 18,
		E_VK_PAUSE = 19,
		E_VK_CAPSLOCK = 20,
		/////////////////
		/////////////////
		E_VK_ESCAPE = 27,
		E_VK_SPACEBAR = 32,
		E_VK_LEFT = 37,
		E_VK_UP = 38,
		E_VK_RIGHT = 39,
		E_VK_DOWN = 40,
		E_VK_KEY0 = 48,
		E_VK_KEY1 = 49,
		E_VK_KEY2 = 50,
		E_VK_KEY3 = 51,
		E_VK_KEY4 = 52,
		E_VK_KEY5 = 53,
		E_VK_KEY6 = 54,
		E_VK_KEY7 = 55,
		E_VK_KEY8 = 56,
		E_VK_KEY9 = 57,
		/////////////////
		E_VK_A = 65,
		E_VK_B,
		E_VK_C,
		E_VK_D,
		E_VK_E,
		E_VK_F,
		E_VK_G,
		E_VK_H,
		E_VK_I,
		E_VK_J,
		E_VK_K,
		E_VK_L,
		E_VK_M,
		E_VK_N,
		E_VK_O,
		E_VK_P,
		E_VK_Q,
		E_VK_R,
		E_VK_S,
		E_VK_T,
		E_VK_U,
		E_VK_V,
		E_VK_W,
		E_VK_X,
		E_VK_Y,
		E_VK_Z,
		E_VK_LWIN = 91,
		E_VK_RWIN = 92,
		E_VK_FN1 = 112,
		E_VK_FN2,
		E_VK_FN3,
		E_VK_FN4,
		E_VK_FN5,
		E_VK_FN6,
		E_VK_FN7,
		E_VK_FN8,
		E_VK_FN9,
		E_VK_FN10,
		E_VK_LSHIFT = 160,
		E_VK_RSHIFT = 161,
		E_VK_LCONTROL = 162,
		E_VK_RCONTROL = 163,
		E_VK_SLASH = 191,
		E_VK_TILDE = 192,
		E_VK_SQBEG = 219,
		E_VK_SQEND = 221,
		E_VK_BKSLSH = 220,
		E_VK_QUOT = 222,
	};

	constexpr EKey mapKeysFromEVK[] = {
		E_KEY_UNDEFINED, // no  value
		/////////////////////////////
		E_KEY_MOUSE_BUTTON,
		E_KEY_MOUSE_BUTTON,
		E_KEY_UNDEFINED, // 'cancel', i dunno
		E_KEY_MOUSE_BUTTON,
		E_KEY_MOUSE_BUTTON,
		E_KEY_MOUSE_BUTTON,
		E_KEY_UNDEFINED, // reserved
		E_KEY_BACKSPACE,
		E_KEY_TAB,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // clear
		E_KEY_ENTER,
		E_KEY_UNDEFINED, // reserved
		E_KEY_MOUSE_BUTTON, // reserved
		E_KEY_SHIFT,
		E_KEY_CONTROL,
		E_KEY_ALT,
		E_KEY_UNDEFINED, // pause
		E_KEY_CAPSLOCK,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_ESCAPE,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_SPACE,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_ARROW_L,
		E_KEY_ARROW_U,
		E_KEY_ARROW_R,
		E_KEY_ARROW_D,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_0,
		E_KEY_1,
		E_KEY_2,
		E_KEY_3,
		E_KEY_4,
		E_KEY_5,
		E_KEY_6,
		E_KEY_7,
		E_KEY_8,
		E_KEY_9,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_A,
		E_KEY_B,
		E_KEY_C,
		E_KEY_D,
		E_KEY_E,
		E_KEY_F,
		E_KEY_G,
		E_KEY_H,
		E_KEY_I,
		E_KEY_J,
		E_KEY_K,
		E_KEY_L,
		E_KEY_M,
		E_KEY_N,
		E_KEY_O,
		E_KEY_P,
		E_KEY_Q,
		E_KEY_R,
		E_KEY_S,
		E_KEY_T,
		E_KEY_U,
		E_KEY_V,
		E_KEY_W,
		E_KEY_X,
		E_KEY_Y,
		E_KEY_Z,
		E_KEY_SUPER,
		E_KEY_SUPER,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_FUNC1,
		E_KEY_FUNC2,
		E_KEY_FUNC3,
		E_KEY_FUNC4,
		E_KEY_FUNC5,
		E_KEY_FUNC6,
		E_KEY_FUNC7,
		E_KEY_FUNC8,
		E_KEY_FUNC9,
		E_KEY_FUNC10,
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_UNDEFINED, // reserved
		E_KEY_SHIFT,
		E_KEY_SHIFT,
		E_KEY_CONTROL,
		E_KEY_CONTROL,
		E_KEY_SLASH,
		E_KEY_APOSTROPHE,
		E_KEY_SQUAREOPEN,
		E_KEY_SQUARECLOSE,
		E_KEY_BACKSLASH,
		E_KEY_QUOT
	};

	constexpr EKeyMod mapModsFromEVK[] = {
		E_KEY_MOD_ANY, // no  value
		/////////////////////////////
		E_KEY_MOD_LEFT,
		E_KEY_MOD_RIGHT,
		E_KEY_MOD_ANY, // 'cancel', i dunno
		E_KEY_MOD_MIDDLE,
		E_KEY_MOD_EXTRA1,
		E_KEY_MOD_EXTRA2,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // clear
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_MIDDLE,	// NOTE: for mouse handling this set to MIDDLE
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // pause
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_LEFT,
		E_KEY_MOD_RIGHT,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_ANY, // reserved
		E_KEY_MOD_LEFT,
		E_KEY_MOD_RIGHT,
		E_KEY_MOD_LEFT,
		E_KEY_MOD_RIGHT,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
		E_KEY_MOD_ANY,
	};

	enum EWindowEvent {
		E_WINDOW_EVENT_NONE,
		E_WINDOW_EVENT_QUIT,
		E_WINDOW_EVENT_CLOSE,
		E_WINDOW_EVENT_RESIZE,
		E_WINDOW_EVENT_ENTER_FOCUS,
		E_WINDOW_EVENT_EXIT_FOCUS,
		E_WINDOW_EVENT_KEY_PRESSED,
		E_WINDOW_EVENT_KEY_RELEASED,
		E_WINDOW_EVENT_CHAR,
		E_WINDOW_EVENT_MOUSE_PRESSED,
		E_WINDOW_EVENT_MOUSE_RELEASED,
		E_WINDOW_EVENT_MOUSE_MOVE,
		E_WINDOW_EVENT_MOVE,
	};

	enum EWaitResult {
		E_WAIT_ABANDONED = 0x00000080L,
		E_WAIT_OBJECT_0  = 0x00000000L,
		E_WAIT_TIMEOUT   = 0x00000102L,
		E_WAIT_FAILED    = 0xFFFFFFFF
	};

	struct SWindowEventData {
		EWindowEvent type;
		union {
			struct {
				int32 width;
				int32 height;
			} onResize;
			struct {
				EVirtualKey evk;
				bool isPressed;
			} onKey;
			char* onChar;
			struct {
				EVirtualKey evk;
				bool isPressed;
			} onMouse;
			struct {
				real x;
				real y;
			} onMouseMove;
			struct {
				int32 x;
				int32 y;
			} onMove;
		};
	};

	using PFNWindowMessageProc = void(*)(HWND hWnd, const SWindowEventData& msg);

	NW_API HINSTANCE	getCurrentPlatformHandle(void);
	NW_API HANDLE		getProcessHeap(void);
	NW_API LPVOID		heapAlloc(HANDLE hHeap, uint64 size, HeapAllocFlags flags);
	NW_API void			heapFree(HANDLE hHeap, void* p);

	NW_API DWORD		getLastError(void);
	NW_API DWORD		getLastErrorStringA(char* s);
	NW_API DWORD		getLastErrorStringW(wchar_t* s);

	NW_API LPVOID		copyMemory(LPVOID dst, LPVOID src, uint64 size);
	NW_API LPVOID		fillMemory(LPVOID dst, int32 value, uint64 size);
	NW_API bool			compareMemory(CLPVOID p1, CLPVOID p2, uint64 size);

	NW_API uint64		lstrlenA(const char* s);
	NW_API uint64		lstrlenW(const wchar_t* s);

	NW_API void			getKeyboardState(uint8 state[256]);

	NW_API BOOL			allocConsole(void);
	NW_API void			freeConsole(void);
	NW_API HANDLE		getStdOutHandle(void);
	NW_API void			writeConsoleA(HANDLE hConsole, const char* text);
	NW_API void			writeConsoleW(HANDLE hConsole, const wchar_t* text);
	NW_API void			writeConsoleA(HANDLE hConsole, const char* text, uint64 len);
	NW_API void			writeConsoleW(HANDLE hConsole, const wchar_t* text, uint64 len);
	NW_API HWND			getConsoleWindow(void);

	NW_API HWND			createWindowW(const wchar_t* title, int32 x, int32 y, int32 w, int32 h, WindowFlags flags, PFNWindowMessageProc proc);
	NW_API HWND			createWindowA(const char* title, int32 x, int32 y, int32 w, int32 h, WindowFlags flags, PFNWindowMessageProc proc);
	NW_API void			destroyWindow(HWND hWnd);
	NW_API void			setWindowLongPtrW(HWND hWnd, WindowLongPtrName name, ptraddr ptraddress);
	NW_API void			setWindowLongPtrA(HWND hWnd, WindowLongPtrName name, ptraddr ptraddress);
	NW_API ptraddr		getWindowLongPtrW(HWND hWnd, WindowLongPtrName name);
	NW_API ptraddr		getWindowLongPtrA(HWND hWnd, WindowLongPtrName name);
	NW_API void			setWindowTextA(HWND hWnd, const char* text);
	NW_API void			setWindowTextW(HWND hWnd, const wchar_t* text);
	NW_API void			showWindow(HWND hWnd, WindowShowFlags flags);
	NW_API BOOL			peekWindowMessagesA(HWND hWnd);
	NW_API BOOL			peekWindowMessagesW(HWND hWnd);

	NW_API uint64		getPrimaryMonitorWidth(void);
	NW_API uint64		getPrimaryMonitorHeight(void);

	NW_API void			sleep(DWORD dwMilliseconds);

	NW_API void			queryPerformanceFrequency(int64& freq);
	NW_API void			queryPerformanceCounter(int64& cnt);

	NW_API void			exitProcess(uint32 code);
	NW_API void			breakProcess(void);

	NW_API void			outputDebugStringA(const char* str);
	NW_API void			outputDebugStringW(const wchar_t* str);

	NW_API HANDLE		createThread(void(*pfnStartProc)(void*), void* params, DWORD* pId);
	NW_API DWORD		resumeThread(HANDLE hThread);
	NW_API void			closeHandle(HANDLE handle);
	NW_API void			getExitCodeThread(HANDLE hThread, DWORD* pExitcode);
	NW_API void			terminateThread(HANDLE hThread, DWORD exitcode);
	NW_API EWaitResult	waitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);

	NW_API uint			interlockValue(volatile uint* pValue);

	NW_API bool			beginCreateOpenGLContext(void);
	NW_API void*		endCreateOpenGLContext(HWND);
	NW_API void			swapBuffers(HWND);

	NW_API void*		loadLibrary(const CHAR* pname);
	NW_API void			closeLibrary(void* phandle);
	NW_API void*		loadProcAddress(void* phandle, const CHAR* psym);

//
//	typedef int (__stdcall* PFNCHOOSEPIXELFORMATPROC)(HDC hDc, const PIXELFORMATDESCRIPTOR* pPfd);
//	typedef int (__stdcall* PFNDESCRIBEPIXELFORMATPROC)(HDC hdc, int ipfd, UINT cjpfd, PIXELFORMATDESCRIPTOR* ppfd);
//	typedef UINT(__stdcall* PFNGETENHMETAFILEPIXELFORMATPROC)(HENHMETAFILE hemf, UINT cbBuffer, PIXELFORMATDESCRIPTOR* ppfd);
//	typedef int (__stdcall* PFNGETPIXELFORMATPROC)(HDC hdc);
//	typedef BOOL(__stdcall* PFNSETPIXELFORMATPROC)(HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR* ppfd);
//	typedef BOOL(__stdcall* PFNSWAPBUFFERSPROC)(HDC hdc);
//	typedef void* (__stdcall* PFNWGLALLOCATEMEMORYNVPROC)(OGL::GLsizei size, OGL::GLfloat readfreq, OGL::GLfloat writefreq, OGL::GLfloat priority);
//	typedef BOOL(__stdcall* PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const HANDLE* pEvent, const LPVOID* pAddress, const DWORD* pSize, UINT count);
//	typedef BOOL(__stdcall* PFNWGLBEGINFRAMETRACKINGI3DPROC)(void);
//	typedef OGL::GLboolean(__stdcall* PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)(OGL::GLushort id);
//	typedef BOOL(__stdcall* PFNWGLBINDSWAPBARRIERNVPROC)(OGL::GLuint group, OGL::GLuint barrier);
//	typedef BOOL(__stdcall* PFNWGLBINDTEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
//	typedef BOOL(__stdcall* PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)(UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice);
//	typedef BOOL(__stdcall* PFNWGLBINDVIDEODEVICENVPROC)(HDC hDc, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int* piAttribList);
//	typedef BOOL(__stdcall* PFNWGLBINDVIDEOIMAGENVPROC)(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);
//	typedef void(__stdcall* PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)(HGLRC dstCtx, OGL::GLint srcX0, OGL::GLint srcY0, OGL::GLint srcX1, OGL::GLint srcY1, OGL::GLint dstX0, OGL::GLint dstY0, OGL::GLint dstX1, OGL::GLint dstY1, OGL::GLbitfield mask, OGL::GLenum filter);
//	typedef BOOL(__stdcall* PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int* piAttribIList, const float* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
//	typedef BOOL(__stdcall* PFNWGLCHOOSEPIXELFORMATEXTPROC)(HDC hdc, const int* piAttribIList, const float* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
//	typedef BOOL(__stdcall* PFNWGLCOPYCONTEXTPROC)(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask);
//	typedef BOOL(__stdcall* PFNWGLCOPYIMAGESUBDATANVPROC)(HGLRC hSrcRC, OGL::GLuint srcName, OGL::GLenum srcTarget, OGL::GLint srcLevel, OGL::GLint srcX, OGL::GLint srcY, OGL::GLint srcZ, HGLRC hDstRC, OGL::GLuint dstName, OGL::GLenum dstTarget, OGL::GLint dstLevel, OGL::GLint dstX, OGL::GLint dstY, OGL::GLint dstZ, OGL::GLsizei width, OGL::GLsizei height, OGL::GLsizei depth);
//	typedef HDC(__stdcall* PFNWGLCREATEAFFINITYDCNVPROC)(const HGPUNV* phGpuList);
//	typedef HGLRC(__stdcall* PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)(UINT id);
//	typedef HGLRC(__stdcall* PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)(UINT id, HGLRC hShareContext, const int* attribList);
//	typedef HANDLE(__stdcall* PFNWGLCREATEBUFFERREGIONARBPROC)(HDC hDC, int iLayerPlane, UINT uType);
//	typedef HGLRC(__stdcall* PFNWGLCREATECONTEXTPROC)(HDC hDc);
//	typedef HGLRC(__stdcall* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);
//	typedef OGL::GLboolean(__stdcall* PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)(OGL::GLushort id);
//	typedef LPVOID(__stdcall* PFNWGLCREATEIMAGEBUFFERI3DPROC)(HDC hDC, DWORD dwSize, UINT uFlags);
//	typedef HGLRC(__stdcall* PFNWGLCREATELAYERCONTEXTPROC)(HDC hDc, int level);
//	typedef HPBUFFERARB(__stdcall* PFNWGLCREATEPBUFFERARBPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int* piAttribList);
//	typedef HPBUFFEREXT(__stdcall* PFNWGLCREATEPBUFFEREXTPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int* piAttribList);
//	typedef BOOL(__stdcall* PFNWGLDXCLOSEDEVICENVPROC)(HANDLE hDevice);
//	typedef BOOL(__stdcall* PFNWGLDXLOCKOBJECTSNVPROC)(HANDLE hDevice, OGL::GLint count, HANDLE* hObjects);
//	typedef BOOL(__stdcall* PFNWGLDXOBJECTACCESSNVPROC)(HANDLE hObject, OGL::GLenum access);
//	typedef HANDLE(__stdcall* PFNWGLDXOPENDEVICENVPROC)(void* dxDevice);
//	typedef HANDLE(__stdcall* PFNWGLDXREGISTEROBJECTNVPROC)(HANDLE hDevice, void* dxObject, OGL::GLuint name, OGL::GLenum type, OGL::GLenum access);
//	typedef BOOL(__stdcall* PFNWGLDXSETRESOURCESHAREHANDLENVPROC)(void* dxObject, HANDLE shareHandle);
//	typedef BOOL(__stdcall* PFNWGLDXUNLOCKOBJECTSNVPROC)(HANDLE hDevice, OGL::GLint count, HANDLE* hObjects);
//	typedef BOOL(__stdcall* PFNWGLDXUNREGISTEROBJECTNVPROC)(HANDLE hDevice, HANDLE hObject);
//	typedef BOOL(__stdcall* PFNWGLDELAYBEFORESWAPNVPROC)(HDC hDC, OGL::GLfloat seconds);
//	typedef BOOL(__stdcall* PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)(HGLRC hglrc);
//	typedef void(__stdcall* PFNWGLDELETEBUFFERREGIONARBPROC)(HANDLE hRegion);
//	typedef BOOL(__stdcall* PFNWGLDELETECONTEXTPROC)(HGLRC oldContext);
//	typedef BOOL(__stdcall* PFNWGLDELETEDCNVPROC)(HDC hdc);
//	typedef BOOL(__stdcall* PFNWGLDESCRIBELAYERPLANEPROC)(HDC hDc, int pixelFormat, int layerPlane, UINT nBytes, LAYERPLANEDESCRIPTOR* plpd);
//	typedef void(__stdcall* PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)(OGL::GLushort id);
//	typedef BOOL(__stdcall* PFNWGLDESTROYIMAGEBUFFERI3DPROC)(HDC hDC, LPVOID pAddress);
//	typedef BOOL(__stdcall* PFNWGLDESTROYPBUFFERARBPROC)(HPBUFFERARB hPbuffer);
//	typedef BOOL(__stdcall* PFNWGLDESTROYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer);
//	typedef BOOL(__stdcall* PFNWGLDISABLEFRAMELOCKI3DPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLDISABLEGENLOCKI3DPROC)(HDC hDC);
//	typedef BOOL(__stdcall* PFNWGLENABLEFRAMELOCKI3DPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLENABLEGENLOCKI3DPROC)(HDC hDC);
//	typedef BOOL(__stdcall* PFNWGLENDFRAMETRACKINGI3DPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLENUMGPUDEVICESNVPROC)(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);
//	typedef BOOL(__stdcall* PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)(HDC hAffinityDC, UINT iGpuIndex, HGPUNV* hGpu);
//	typedef BOOL(__stdcall* PFNWGLENUMGPUSNVPROC)(UINT iGpuIndex, HGPUNV* phGpu);
//	typedef UINT(__stdcall* PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)(HDC hDc, HVIDEOINPUTDEVICENV* phDeviceList);
//	typedef int (__stdcall* PFNWGLENUMERATEVIDEODEVICESNVPROC)(HDC hDc, HVIDEOOUTPUTDEVICENV* phDeviceList);
//	typedef void (__stdcall* PFNWGLFREEMEMORYNVPROC)(void* pointer);
//	typedef BOOL(__stdcall* PFNWGLGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT uRate);
//	typedef BOOL(__stdcall* PFNWGLGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT uDelay);
//	typedef BOOL(__stdcall* PFNWGLGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT uEdge);
//	typedef BOOL(__stdcall* PFNWGLGENLOCKSOURCEI3DPROC)(HDC hDC, UINT uSource);
//	typedef UINT(__stdcall* PFNWGLGETCONTEXTGPUIDAMDPROC)(HGLRC hglrc);
//	typedef HGLRC(__stdcall* PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)(void);
//	typedef HGLRC(__stdcall* PFNWGLGETCURRENTCONTEXTPROC)(void);
//	typedef HDC(__stdcall* PFNWGLGETCURRENTDCPROC)(void);
//	typedef HDC(__stdcall* PFNWGLGETCURRENTREADDCARBPROC)(void);
//	typedef HDC(__stdcall* PFNWGLGETCURRENTREADDCEXTPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int* piValue);
//	typedef const char* (__stdcall* PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
//	typedef const char* (__stdcall* PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLGETFRAMEUSAGEI3DPROC)(float* pUsage);
//	typedef UINT(__stdcall* PFNWGLGETGPUIDSAMDPROC)(UINT maxCount, UINT* ids);
//	typedef int(__stdcall* PFNWGLGETGPUINFOAMDPROC)(UINT id, int property, OGL::GLenum dataType, UINT size, void* data);
//	typedef BOOL(__stdcall* PFNWGLGETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, uint16* puRed, uint16* puGreen, uint16* puBlue);
//	typedef BOOL(__stdcall* PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int* piValue);
//	typedef BOOL(__stdcall* PFNWGLGETGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT* uRate);
//	typedef BOOL(__stdcall* PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT* uDelay);
//	typedef BOOL(__stdcall* PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT* uEdge);
//	typedef BOOL(__stdcall* PFNWGLGETGENLOCKSOURCEI3DPROC)(HDC hDC, UINT* uSource);
//	typedef int (__stdcall* PFNWGLGETLAYERPALETTEENTRIESPROC)(HDC hdc, int iLayerPlane, int iStart, int cEntries, COLORREF* pcr);
//	typedef BOOL(__stdcall* PFNWGLGETMSCRATEOMLPROC)(HDC hdc, int32* numerator, int32* denominator);
//	typedef HDC(__stdcall* PFNWGLGETPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer);
//	typedef HDC(__stdcall* PFNWGLGETPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer);
//	typedef BOOL(__stdcall* PFNWGLGETPIXELFORMATATTRIBFVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int* piAttributes, float* pfValues);
//	typedef BOOL(__stdcall* PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int* piAttributes, float* pfValues);
//	typedef BOOL(__stdcall* PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int* piAttributes, int* piValues);
//	typedef BOOL(__stdcall* PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int* piAttributes, int* piValues);
//	typedef PROC(__stdcall* PFNWGLGETPROCADDRESSPROC)(const char *lpszProc);
//	typedef int (__stdcall* PFNWGLGETSWAPINTERVALEXTPROC)(void);
//	typedef BOOL(__stdcall* PFNWGLGETSYNCVALUESOMLPROC)(HDC hdc, int64* ust, int64* msc, int64* sbc);
//	typedef BOOL(__stdcall* PFNWGLGETVIDEODEVICENVPROC)(HDC hDC, int numDevices, HPVIDEODEV* hVideoDevice);
//	typedef BOOL(__stdcall* PFNWGLGETVIDEOINFONVPROC)(HPVIDEODEV hpVideoDevice, unsigned long* pulCounterOutputPbuffer, unsigned long* pulCounterOutputVideo);
//	typedef BOOL(__stdcall* PFNWGLISENABLEDFRAMELOCKI3DPROC)(BOOL* pFlag);
//	typedef BOOL(__stdcall* PFNWGLISENABLEDGENLOCKI3DPROC)(HDC hDC, BOOL* pFlag);
//	typedef BOOL(__stdcall* PFNWGLJOINSWAPGROUPNVPROC)(HDC hDC, OGL::GLuint group);
//	typedef OGL::GLboolean(__stdcall* PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)(const OGL::GLushort* table, OGL::GLuint length);
//	typedef BOOL(__stdcall* PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice);
//	typedef BOOL(__stdcall* PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)(HGLRC hglrc);
//	typedef BOOL(__stdcall* PFNWGLMAKECONTEXTCURRENTARBPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
//	typedef BOOL(__stdcall* PFNWGLMAKECONTEXTCURRENTEXTPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
//	typedef BOOL(__stdcall* PFNWGLMAKECURRENTPROC)(HDC hDc, HGLRC newContext);
//	typedef BOOL(__stdcall* PFNWGLQUERYCURRENTCONTEXTNVPROC)(int iAttribute, int* piValue);
//	typedef BOOL(__stdcall* PFNWGLQUERYFRAMECOUNTNVPROC)(HDC hDC, OGL::GLuint* count);
//	typedef BOOL(__stdcall* PFNWGLQUERYFRAMELOCKMASTERI3DPROC)(BOOL* pFlag);
//	typedef BOOL(__stdcall* PFNWGLQUERYFRAMETRACKINGI3DPROC)(DWORD* pFrameCount, DWORD* pMissedFrames, float* pLastMissedUsage);
//	typedef BOOL(__stdcall* PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)(HDC hDC, UINT* uMaxLineDelay, UINT* uMaxPixelDelay);
//	typedef BOOL(__stdcall* PFNWGLQUERYMAXSWAPGROUPSNVPROC)(HDC hDC, OGL::GLuint* maxGroups, OGL::GLuint* maxBarriers);
//	typedef BOOL(__stdcall* PFNWGLQUERYPBUFFERARBPROC)(HPBUFFERARB hPbuffer, int iAttribute, int* piValue);
//	typedef BOOL(__stdcall* PFNWGLQUERYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer, int iAttribute, int* piValue);
//	typedef BOOL(__stdcall* PFNWGLQUERYSWAPGROUPNVPROC)(HDC hDC, OGL::GLuint* group, OGL::GLuint* barrier);
//	typedef BOOL(__stdcall* PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int* piValue);
//	typedef BOOL(__stdcall* PFNWGLREALIZELAYERPALETTEPROC)(HDC hdc, int iLayerPlane, BOOL bRealize);
//	typedef BOOL(__stdcall* PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const LPVOID* pAddress, UINT count);
//	typedef int (__stdcall* PFNWGLRELEASEPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer, HDC hDC);
//	typedef int (__stdcall* PFNWGLRELEASEPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer, HDC hDC);
//	typedef BOOL(__stdcall* PFNWGLRELEASETEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
//	typedef BOOL(__stdcall* PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice);
//	typedef BOOL(__stdcall* PFNWGLRELEASEVIDEODEVICENVPROC)(HPVIDEODEV hVideoDevice);
//	typedef BOOL(__stdcall* PFNWGLRELEASEVIDEOIMAGENVPROC)(HPBUFFERARB hPbuffer, int iVideoBuffer);
//	typedef BOOL(__stdcall* PFNWGLRESETFRAMECOUNTNVPROC)(HDC hDC);
//	typedef BOOL(__stdcall* PFNWGLRESTOREBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);
//	typedef BOOL(__stdcall* PFNWGLSAVEBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height);
//	typedef BOOL(__stdcall* PFNWGLSENDPBUFFERTOVIDEONVPROC)(HPBUFFERARB hPbuffer, int iBufferType, unsigned long* pulCounterPbuffer, BOOL bBlock);
//	typedef BOOL(__stdcall* PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int* piValue);
//	typedef BOOL(__stdcall* PFNWGLSETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, const uint16* puRed, const uint16* puGreen, const uint16* puBlue);
//	typedef BOOL(__stdcall* PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int* piValue);
//	typedef int (__stdcall* PFNWGLSETLAYERPALETTEENTRIESPROC)(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF* pcr);
//	typedef BOOL(__stdcall* PFNWGLSETPBUFFERATTRIBARBPROC)(HPBUFFERARB hPbuffer, const int* piAttribList);
//	typedef BOOL(__stdcall* PFNWGLSETSTEREOEMITTERSTATE3DLPROC)(HDC hDC, UINT uState);
//	typedef BOOL(__stdcall* PFNWGLSHARELISTSPROC)(HGLRC hrcSrvShare, HGLRC hrcSrvSource);
//	typedef int64(__stdcall* PFNWGLSWAPBUFFERSMSCOMLPROC)(HDC hdc, int64 target_msc, int64 divisor, int64 remainder);
//	typedef BOOL(__stdcall* PFNWGLSWAPINTERVALEXTPROC)(int interval);
//	typedef BOOL(__stdcall* PFNWGLSWAPLAYERBUFFERSPROC)(HDC hdc, UINT fuFlags);
//	typedef int64(__stdcall* PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)(HDC hdc, int32 fuPlanes, int64 target_msc, int64 divisor, int64 remainder);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTBITMAPSPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTBITMAPSAPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTBITMAPSWPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTOUTLINESPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, float deviation, float extrusion, int format, GLYPHMETRICSFLOAT* lpgmf);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTOUTLINESAPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, float deviation, float extrusion, int format, GLYPHMETRICSFLOAT* lpgmf);
//	typedef BOOL(__stdcall* PFNWGLUSEFONTOUTLINESWPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, float deviation, float extrusion, int format, GLYPHMETRICSFLOAT* lpgmf);
//	typedef BOOL(__stdcall* PFNWGLWAITFORMSCOMLPROC)(HDC hdc, int64 target_msc, int64 divisor, int64 remainder, int64* ust, int64* msc, int64* sbc);
//	typedef BOOL(__stdcall* PFNWGLWAITFORSBCOMLPROC)(HDC hdc, int64 target_sbc, int64* ust, int64* msc, int64* sbc);
//
//
//	extern PFNWGLALLOCATEMEMORYNVPROC glad_wglAllocateMemoryNV;
//#define wglAllocateMemoryNV glad_wglAllocateMemoryNV
//	extern PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC glad_wglAssociateImageBufferEventsI3D;
//#define wglAssociateImageBufferEventsI3D glad_wglAssociateImageBufferEventsI3D
//	extern PFNWGLBEGINFRAMETRACKINGI3DPROC glad_wglBeginFrameTrackingI3D;
//#define wglBeginFrameTrackingI3D glad_wglBeginFrameTrackingI3D
//	extern PFNWGLBINDDISPLAYCOLORTABLEEXTPROC glad_wglBindDisplayColorTableEXT;
//#define wglBindDisplayColorTableEXT glad_wglBindDisplayColorTableEXT
//	extern PFNWGLBINDSWAPBARRIERNVPROC glad_wglBindSwapBarrierNV;
//#define wglBindSwapBarrierNV glad_wglBindSwapBarrierNV
//	extern PFNWGLBINDTEXIMAGEARBPROC glad_wglBindTexImageARB;
//#define wglBindTexImageARB glad_wglBindTexImageARB
//	extern PFNWGLBINDVIDEOCAPTUREDEVICENVPROC glad_wglBindVideoCaptureDeviceNV;
//#define wglBindVideoCaptureDeviceNV glad_wglBindVideoCaptureDeviceNV
//	extern PFNWGLBINDVIDEODEVICENVPROC glad_wglBindVideoDeviceNV;
//#define wglBindVideoDeviceNV glad_wglBindVideoDeviceNV
//	extern PFNWGLBINDVIDEOIMAGENVPROC glad_wglBindVideoImageNV;
//#define wglBindVideoImageNV glad_wglBindVideoImageNV
//	extern PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC glad_wglBlitContextFramebufferAMD;
//#define wglBlitContextFramebufferAMD glad_wglBlitContextFramebufferAMD
//	extern PFNWGLCHOOSEPIXELFORMATARBPROC glad_wglChoosePixelFormatARB;
//#define wglChoosePixelFormatARB glad_wglChoosePixelFormatARB
//	extern PFNWGLCHOOSEPIXELFORMATEXTPROC glad_wglChoosePixelFormatEXT;
//#define wglChoosePixelFormatEXT glad_wglChoosePixelFormatEXT
//	extern PFNWGLCOPYIMAGESUBDATANVPROC glad_wglCopyImageSubDataNV;
//#define wglCopyImageSubDataNV glad_wglCopyImageSubDataNV
//	extern PFNWGLCREATEAFFINITYDCNVPROC glad_wglCreateAffinityDCNV;
//#define wglCreateAffinityDCNV glad_wglCreateAffinityDCNV
//	extern PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC glad_wglCreateAssociatedContextAMD;
//#define wglCreateAssociatedContextAMD glad_wglCreateAssociatedContextAMD
//	extern PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC glad_wglCreateAssociatedContextAttribsAMD;
//#define wglCreateAssociatedContextAttribsAMD glad_wglCreateAssociatedContextAttribsAMD
//	extern PFNWGLCREATEBUFFERREGIONARBPROC glad_wglCreateBufferRegionARB;
//#define wglCreateBufferRegionARB glad_wglCreateBufferRegionARB
//	extern PFNWGLCREATECONTEXTATTRIBSARBPROC glad_wglCreateContextAttribsARB;
//#define wglCreateContextAttribsARB glad_wglCreateContextAttribsARB
//	extern PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC glad_wglCreateDisplayColorTableEXT;
//#define wglCreateDisplayColorTableEXT glad_wglCreateDisplayColorTableEXT
//	extern PFNWGLCREATEIMAGEBUFFERI3DPROC glad_wglCreateImageBufferI3D;
//#define wglCreateImageBufferI3D glad_wglCreateImageBufferI3D
//	extern PFNWGLCREATEPBUFFERARBPROC glad_wglCreatePbufferARB;
//#define wglCreatePbufferARB glad_wglCreatePbufferARB
//	extern PFNWGLCREATEPBUFFEREXTPROC glad_wglCreatePbufferEXT;
//#define wglCreatePbufferEXT glad_wglCreatePbufferEXT
//	extern PFNWGLDXCLOSEDEVICENVPROC glad_wglDXCloseDeviceNV;
//#define wglDXCloseDeviceNV glad_wglDXCloseDeviceNV
//	extern PFNWGLDXLOCKOBJECTSNVPROC glad_wglDXLockObjectsNV;
//#define wglDXLockObjectsNV glad_wglDXLockObjectsNV
//	extern PFNWGLDXOBJECTACCESSNVPROC glad_wglDXObjectAccessNV;
//#define wglDXObjectAccessNV glad_wglDXObjectAccessNV
//	extern PFNWGLDXOPENDEVICENVPROC glad_wglDXOpenDeviceNV;
//#define wglDXOpenDeviceNV glad_wglDXOpenDeviceNV
//	extern PFNWGLDXREGISTEROBJECTNVPROC glad_wglDXRegisterObjectNV;
//#define wglDXRegisterObjectNV glad_wglDXRegisterObjectNV
//	extern PFNWGLDXSETRESOURCESHAREHANDLENVPROC glad_wglDXSetResourceShareHandleNV;
//#define wglDXSetResourceShareHandleNV glad_wglDXSetResourceShareHandleNV
//	extern PFNWGLDXUNLOCKOBJECTSNVPROC glad_wglDXUnlockObjectsNV;
//#define wglDXUnlockObjectsNV glad_wglDXUnlockObjectsNV
//	extern PFNWGLDXUNREGISTEROBJECTNVPROC glad_wglDXUnregisterObjectNV;
//#define wglDXUnregisterObjectNV glad_wglDXUnregisterObjectNV
//	extern PFNWGLDELAYBEFORESWAPNVPROC glad_wglDelayBeforeSwapNV;
//#define wglDelayBeforeSwapNV glad_wglDelayBeforeSwapNV
//	extern PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC glad_wglDeleteAssociatedContextAMD;
//#define wglDeleteAssociatedContextAMD glad_wglDeleteAssociatedContextAMD
//	extern PFNWGLDELETEBUFFERREGIONARBPROC glad_wglDeleteBufferRegionARB;
//#define wglDeleteBufferRegionARB glad_wglDeleteBufferRegionARB
//	extern PFNWGLDELETEDCNVPROC glad_wglDeleteDCNV;
//#define wglDeleteDCNV glad_wglDeleteDCNV
//	extern PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC glad_wglDestroyDisplayColorTableEXT;
//#define wglDestroyDisplayColorTableEXT glad_wglDestroyDisplayColorTableEXT
//	extern PFNWGLDESTROYIMAGEBUFFERI3DPROC glad_wglDestroyImageBufferI3D;
//#define wglDestroyImageBufferI3D glad_wglDestroyImageBufferI3D
//	extern PFNWGLDESTROYPBUFFERARBPROC glad_wglDestroyPbufferARB;
//#define wglDestroyPbufferARB glad_wglDestroyPbufferARB
//	extern PFNWGLDESTROYPBUFFEREXTPROC glad_wglDestroyPbufferEXT;
//#define wglDestroyPbufferEXT glad_wglDestroyPbufferEXT
//	extern PFNWGLDISABLEFRAMELOCKI3DPROC glad_wglDisableFrameLockI3D;
//#define wglDisableFrameLockI3D glad_wglDisableFrameLockI3D
//	extern PFNWGLDISABLEGENLOCKI3DPROC glad_wglDisableGenlockI3D;
//#define wglDisableGenlockI3D glad_wglDisableGenlockI3D
//	extern PFNWGLENABLEFRAMELOCKI3DPROC glad_wglEnableFrameLockI3D;
//#define wglEnableFrameLockI3D glad_wglEnableFrameLockI3D
//	extern PFNWGLENABLEGENLOCKI3DPROC glad_wglEnableGenlockI3D;
//#define wglEnableGenlockI3D glad_wglEnableGenlockI3D
//	extern PFNWGLENDFRAMETRACKINGI3DPROC glad_wglEndFrameTrackingI3D;
//#define wglEndFrameTrackingI3D glad_wglEndFrameTrackingI3D
//	extern PFNWGLENUMGPUDEVICESNVPROC glad_wglEnumGpuDevicesNV;
//#define wglEnumGpuDevicesNV glad_wglEnumGpuDevicesNV
//	extern PFNWGLENUMGPUSFROMAFFINITYDCNVPROC glad_wglEnumGpusFromAffinityDCNV;
//#define wglEnumGpusFromAffinityDCNV glad_wglEnumGpusFromAffinityDCNV
//	extern PFNWGLENUMGPUSNVPROC glad_wglEnumGpusNV;
//#define wglEnumGpusNV glad_wglEnumGpusNV
//	extern PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC glad_wglEnumerateVideoCaptureDevicesNV;
//#define wglEnumerateVideoCaptureDevicesNV glad_wglEnumerateVideoCaptureDevicesNV
//	extern PFNWGLENUMERATEVIDEODEVICESNVPROC glad_wglEnumerateVideoDevicesNV;
//#define wglEnumerateVideoDevicesNV glad_wglEnumerateVideoDevicesNV
//	extern PFNWGLFREEMEMORYNVPROC glad_wglFreeMemoryNV;
//#define wglFreeMemoryNV glad_wglFreeMemoryNV
//	extern PFNWGLGENLOCKSAMPLERATEI3DPROC glad_wglGenlockSampleRateI3D;
//#define wglGenlockSampleRateI3D glad_wglGenlockSampleRateI3D
//	extern PFNWGLGENLOCKSOURCEDELAYI3DPROC glad_wglGenlockSourceDelayI3D;
//#define wglGenlockSourceDelayI3D glad_wglGenlockSourceDelayI3D
//	extern PFNWGLGENLOCKSOURCEEDGEI3DPROC glad_wglGenlockSourceEdgeI3D;
//#define wglGenlockSourceEdgeI3D glad_wglGenlockSourceEdgeI3D
//	extern PFNWGLGENLOCKSOURCEI3DPROC glad_wglGenlockSourceI3D;
//#define wglGenlockSourceI3D glad_wglGenlockSourceI3D
//	extern PFNWGLGETCONTEXTGPUIDAMDPROC glad_wglGetContextGPUIDAMD;
//#define wglGetContextGPUIDAMD glad_wglGetContextGPUIDAMD
//	extern PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC glad_wglGetCurrentAssociatedContextAMD;
//#define wglGetCurrentAssociatedContextAMD glad_wglGetCurrentAssociatedContextAMD
//	extern PFNWGLGETCURRENTREADDCARBPROC glad_wglGetCurrentReadDCARB;
//#define wglGetCurrentReadDCARB glad_wglGetCurrentReadDCARB
//	extern PFNWGLGETCURRENTREADDCEXTPROC glad_wglGetCurrentReadDCEXT;
//#define wglGetCurrentReadDCEXT glad_wglGetCurrentReadDCEXT
//	extern PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC glad_wglGetDigitalVideoParametersI3D;
//#define wglGetDigitalVideoParametersI3D glad_wglGetDigitalVideoParametersI3D
//	extern PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB;
//#define wglGetExtensionsStringARB glad_wglGetExtensionsStringARB
//	extern PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT;
//#define wglGetExtensionsStringEXT glad_wglGetExtensionsStringEXT
//	extern PFNWGLGETFRAMEUSAGEI3DPROC glad_wglGetFrameUsageI3D;
//#define wglGetFrameUsageI3D glad_wglGetFrameUsageI3D
//	extern PFNWGLGETGPUIDSAMDPROC glad_wglGetGPUIDsAMD;
//#define wglGetGPUIDsAMD glad_wglGetGPUIDsAMD
//	extern PFNWGLGETGPUINFOAMDPROC glad_wglGetGPUInfoAMD;
//#define wglGetGPUInfoAMD glad_wglGetGPUInfoAMD
//	extern PFNWGLGETGAMMATABLEI3DPROC glad_wglGetGammaTableI3D;
//#define wglGetGammaTableI3D glad_wglGetGammaTableI3D
//	extern PFNWGLGETGAMMATABLEPARAMETERSI3DPROC glad_wglGetGammaTableParametersI3D;
//#define wglGetGammaTableParametersI3D glad_wglGetGammaTableParametersI3D
//	extern PFNWGLGETGENLOCKSAMPLERATEI3DPROC glad_wglGetGenlockSampleRateI3D;
//#define wglGetGenlockSampleRateI3D glad_wglGetGenlockSampleRateI3D
//	extern PFNWGLGETGENLOCKSOURCEDELAYI3DPROC glad_wglGetGenlockSourceDelayI3D;
//#define wglGetGenlockSourceDelayI3D glad_wglGetGenlockSourceDelayI3D
//	extern PFNWGLGETGENLOCKSOURCEEDGEI3DPROC glad_wglGetGenlockSourceEdgeI3D;
//#define wglGetGenlockSourceEdgeI3D glad_wglGetGenlockSourceEdgeI3D
//	extern PFNWGLGETGENLOCKSOURCEI3DPROC glad_wglGetGenlockSourceI3D;
//#define wglGetGenlockSourceI3D glad_wglGetGenlockSourceI3D
//	extern PFNWGLGETMSCRATEOMLPROC glad_wglGetMscRateOML;
//#define wglGetMscRateOML glad_wglGetMscRateOML
//	extern PFNWGLGETPBUFFERDCARBPROC glad_wglGetPbufferDCARB;
//#define wglGetPbufferDCARB glad_wglGetPbufferDCARB
//	extern PFNWGLGETPBUFFERDCEXTPROC glad_wglGetPbufferDCEXT;
//#define wglGetPbufferDCEXT glad_wglGetPbufferDCEXT
//	extern PFNWGLGETPIXELFORMATATTRIBFVARBPROC glad_wglGetPixelFormatAttribfvARB;
//#define wglGetPixelFormatAttribfvARB glad_wglGetPixelFormatAttribfvARB
//	extern PFNWGLGETPIXELFORMATATTRIBFVEXTPROC glad_wglGetPixelFormatAttribfvEXT;
//#define wglGetPixelFormatAttribfvEXT glad_wglGetPixelFormatAttribfvEXT
//	extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC glad_wglGetPixelFormatAttribivARB;
//#define wglGetPixelFormatAttribivARB glad_wglGetPixelFormatAttribivARB
//	extern PFNWGLGETPIXELFORMATATTRIBIVEXTPROC glad_wglGetPixelFormatAttribivEXT;
//#define wglGetPixelFormatAttribivEXT glad_wglGetPixelFormatAttribivEXT
//	extern PFNWGLGETSWAPINTERVALEXTPROC glad_wglGetSwapIntervalEXT;
//#define wglGetSwapIntervalEXT glad_wglGetSwapIntervalEXT
//	extern PFNWGLGETSYNCVALUESOMLPROC glad_wglGetSyncValuesOML;
//#define wglGetSyncValuesOML glad_wglGetSyncValuesOML
//	extern PFNWGLGETVIDEODEVICENVPROC glad_wglGetVideoDeviceNV;
//#define wglGetVideoDeviceNV glad_wglGetVideoDeviceNV
//	extern PFNWGLGETVIDEOINFONVPROC glad_wglGetVideoInfoNV;
//#define wglGetVideoInfoNV glad_wglGetVideoInfoNV
//	extern PFNWGLISENABLEDFRAMELOCKI3DPROC glad_wglIsEnabledFrameLockI3D;
//#define wglIsEnabledFrameLockI3D glad_wglIsEnabledFrameLockI3D
//	extern PFNWGLISENABLEDGENLOCKI3DPROC glad_wglIsEnabledGenlockI3D;
//#define wglIsEnabledGenlockI3D glad_wglIsEnabledGenlockI3D
//	extern PFNWGLJOINSWAPGROUPNVPROC glad_wglJoinSwapGroupNV;
//#define wglJoinSwapGroupNV glad_wglJoinSwapGroupNV
//	extern PFNWGLLOADDISPLAYCOLORTABLEEXTPROC glad_wglLoadDisplayColorTableEXT;
//#define wglLoadDisplayColorTableEXT glad_wglLoadDisplayColorTableEXT
//	extern PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC glad_wglLockVideoCaptureDeviceNV;
//#define wglLockVideoCaptureDeviceNV glad_wglLockVideoCaptureDeviceNV
//	extern PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC glad_wglMakeAssociatedContextCurrentAMD;
//#define wglMakeAssociatedContextCurrentAMD glad_wglMakeAssociatedContextCurrentAMD
//	extern PFNWGLMAKECONTEXTCURRENTARBPROC glad_wglMakeContextCurrentARB;
//#define wglMakeContextCurrentARB glad_wglMakeContextCurrentARB
//	extern PFNWGLMAKECONTEXTCURRENTEXTPROC glad_wglMakeContextCurrentEXT;
//#define wglMakeContextCurrentEXT glad_wglMakeContextCurrentEXT
//	extern PFNWGLQUERYCURRENTCONTEXTNVPROC glad_wglQueryCurrentContextNV;
//#define wglQueryCurrentContextNV glad_wglQueryCurrentContextNV
//	extern PFNWGLQUERYFRAMECOUNTNVPROC glad_wglQueryFrameCountNV;
//#define wglQueryFrameCountNV glad_wglQueryFrameCountNV
//	extern PFNWGLQUERYFRAMELOCKMASTERI3DPROC glad_wglQueryFrameLockMasterI3D;
//#define wglQueryFrameLockMasterI3D glad_wglQueryFrameLockMasterI3D
//	extern PFNWGLQUERYFRAMETRACKINGI3DPROC glad_wglQueryFrameTrackingI3D;
//#define wglQueryFrameTrackingI3D glad_wglQueryFrameTrackingI3D
//	extern PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC glad_wglQueryGenlockMaxSourceDelayI3D;
//#define wglQueryGenlockMaxSourceDelayI3D glad_wglQueryGenlockMaxSourceDelayI3D
//	extern PFNWGLQUERYMAXSWAPGROUPSNVPROC glad_wglQueryMaxSwapGroupsNV;
//#define wglQueryMaxSwapGroupsNV glad_wglQueryMaxSwapGroupsNV
//	extern PFNWGLQUERYPBUFFERARBPROC glad_wglQueryPbufferARB;
//#define wglQueryPbufferARB glad_wglQueryPbufferARB
//	extern PFNWGLQUERYPBUFFEREXTPROC glad_wglQueryPbufferEXT;
//#define wglQueryPbufferEXT glad_wglQueryPbufferEXT
//	extern PFNWGLQUERYSWAPGROUPNVPROC glad_wglQuerySwapGroupNV;
//#define wglQuerySwapGroupNV glad_wglQuerySwapGroupNV
//	extern PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC glad_wglQueryVideoCaptureDeviceNV;
//#define wglQueryVideoCaptureDeviceNV glad_wglQueryVideoCaptureDeviceNV
//	extern PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC glad_wglReleaseImageBufferEventsI3D;
//#define wglReleaseImageBufferEventsI3D glad_wglReleaseImageBufferEventsI3D
//	extern PFNWGLRELEASEPBUFFERDCARBPROC glad_wglReleasePbufferDCARB;
//#define wglReleasePbufferDCARB glad_wglReleasePbufferDCARB
//	extern PFNWGLRELEASEPBUFFERDCEXTPROC glad_wglReleasePbufferDCEXT;
//#define wglReleasePbufferDCEXT glad_wglReleasePbufferDCEXT
//	extern PFNWGLRELEASETEXIMAGEARBPROC glad_wglReleaseTexImageARB;
//#define wglReleaseTexImageARB glad_wglReleaseTexImageARB
//	extern PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC glad_wglReleaseVideoCaptureDeviceNV;
//#define wglReleaseVideoCaptureDeviceNV glad_wglReleaseVideoCaptureDeviceNV
//	extern PFNWGLRELEASEVIDEODEVICENVPROC glad_wglReleaseVideoDeviceNV;
//#define wglReleaseVideoDeviceNV glad_wglReleaseVideoDeviceNV
//	extern PFNWGLRELEASEVIDEOIMAGENVPROC glad_wglReleaseVideoImageNV;
//#define wglReleaseVideoImageNV glad_wglReleaseVideoImageNV
//	extern PFNWGLRESETFRAMECOUNTNVPROC glad_wglResetFrameCountNV;
//#define wglResetFrameCountNV glad_wglResetFrameCountNV
//	extern PFNWGLRESTOREBUFFERREGIONARBPROC glad_wglRestoreBufferRegionARB;
//#define wglRestoreBufferRegionARB glad_wglRestoreBufferRegionARB
//	extern PFNWGLSAVEBUFFERREGIONARBPROC glad_wglSaveBufferRegionARB;
//#define wglSaveBufferRegionARB glad_wglSaveBufferRegionARB
//	extern PFNWGLSENDPBUFFERTOVIDEONVPROC glad_wglSendPbufferToVideoNV;
//#define wglSendPbufferToVideoNV glad_wglSendPbufferToVideoNV
//	extern PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC glad_wglSetDigitalVideoParametersI3D;
//#define wglSetDigitalVideoParametersI3D glad_wglSetDigitalVideoParametersI3D
//	extern PFNWGLSETGAMMATABLEI3DPROC glad_wglSetGammaTableI3D;
//#define wglSetGammaTableI3D glad_wglSetGammaTableI3D
//	extern PFNWGLSETGAMMATABLEPARAMETERSI3DPROC glad_wglSetGammaTableParametersI3D;
//#define wglSetGammaTableParametersI3D glad_wglSetGammaTableParametersI3D
//	extern PFNWGLSETPBUFFERATTRIBARBPROC glad_wglSetPbufferAttribARB;
//#define wglSetPbufferAttribARB glad_wglSetPbufferAttribARB
//	extern PFNWGLSETSTEREOEMITTERSTATE3DLPROC glad_wglSetStereoEmitterState3DL;
//#define wglSetStereoEmitterState3DL glad_wglSetStereoEmitterState3DL
//	extern PFNWGLSWAPBUFFERSMSCOMLPROC glad_wglSwapBuffersMscOML;
//#define wglSwapBuffersMscOML glad_wglSwapBuffersMscOML
//	extern PFNWGLSWAPINTERVALEXTPROC glad_wglSwapIntervalEXT;
//#define wglSwapIntervalEXT glad_wglSwapIntervalEXT
//	extern PFNWGLSWAPLAYERBUFFERSMSCOMLPROC glad_wglSwapLayerBuffersMscOML;
//#define wglSwapLayerBuffersMscOML glad_wglSwapLayerBuffersMscOML
//	extern PFNWGLWAITFORMSCOMLPROC glad_wglWaitForMscOML;
//#define wglWaitForMscOML glad_wglWaitForMscOML
//	extern PFNWGLWAITFORSBCOMLPROC glad_wglWaitForSbcOML;
//#define wglWaitForSbcOML glad_wglWaitForSbcOML
//
//	typedef PROC(*GLADloadfunc)(const char* name);
//	extern int LoadWin32GL(HDC hdc, GLADloadfunc load);

}
