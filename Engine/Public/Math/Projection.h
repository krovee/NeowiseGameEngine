#pragma once

#include "Matrix4.h"

namespace Neowise {
	/** 
	* 
	*/
	enum EProjectionKind : uint {
		E_PROJETION_KIND_PERSPECTIVE,
		E_PROJECTION_KIND_ORTHOGRAPHIC
	};

	/** 
	* 
	*/
	struct IProjectionCreateInfoBase {};

	/** 
	* 
	*/
	struct SProjectionPerspectiveCreateInfo : IProjectionCreateInfoBase {
		FVec2	viewportSize = {};
		real	nearPlaneZ	 = 0.05f;
		real	fovY		 = 70.f;
	};

	/** 
	* 
	*/
	struct SProjectionOrthographicCreateInfo : IProjectionCreateInfoBase {
		real	left		 = 0;
		real	right		 = 0;
		real	top			 = 0;
		real	bottom		 = 0;
		real	nearPlaneZ	 = 0.05f;
		real	farPlaneZ	 = 10.f;
	};

	/** 
	* 
	*/
	class NW_API CProjection {
	public:
		~CProjection() = default;
		constexpr CProjection() = default;

		CProjection(EProjectionKind kind, const IProjectionCreateInfoBase& createInfo);

		void setNearZ(real value);
		void setFarZ(real value);
		void setSize(const FVec2& size);
		void setRectSize(real left, real right, real top, real bottom);
		void setFovY(real value);

		operator FMatrix4() const;

		void updateRequired();
	private:
		void setupPerspective(const SProjectionPerspectiveCreateInfo& createInfo);
		void setupOrthographic(const SProjectionOrthographicCreateInfo& createInfo);
	private:
		FMatrix4		_mat = FMatrix4(1);
		real			_zNear	= 0.05f;
		real			_zFar	= 10000.f;
		real			_fovY	= 70.f;
		real			_left	= 0;
		real			_right	= 0;
		real			_bottom	= 0;
		real			_top	= 0;
		real			_aspect	= 0;
		EProjectionKind	_kind = E_PROJETION_KIND_PERSPECTIVE;
		bool			_dirty	= true;
	};
}
