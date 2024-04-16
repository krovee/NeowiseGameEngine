#pragma once

#include <Math/Matrix4.h>

namespace Neowise {
    /** 
    * 
    */
    enum EProjectionKind : TUint {
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
        TReal	nearPlaneZ	 = 0.05f;
        TReal	fovY		 = 70.f;
    };

    /** 
    * 
    */
    struct SProjectionOrthographicCreateInfo : IProjectionCreateInfoBase {
        TReal	left		 = 0;
        TReal	right		 = 0;
        TReal	top			 = 0;
        TReal	bottom		 = 0;
        TReal	nearPlaneZ	 = 0.05f;
        TReal	farPlaneZ	 = 10.f;
    };

    /** 
    * 
    */
    class NW_API CProjection {
    public:
        ~CProjection() = default;
        constexpr CProjection() = default;

        CProjection(EProjectionKind kind, const IProjectionCreateInfoBase* pCreateInfo);

        void setNearZ(TReal value);
        void setFarZ(TReal value);
        void setSize(const FVec2& size);
        void setRectSize(TReal left, TReal right, TReal top, TReal bottom);
        void setFovY(TReal value);

        operator FMatrix4() const;

        void updateRequired();
    private:
        void setupPerspective(const SProjectionPerspectiveCreateInfo* pCreateInfo);
        void setupOrthographic(const SProjectionOrthographicCreateInfo* pCreateInfo);
    private:
        FMatrix4		_mat = FMatrix4(1);
        TReal			_zNear	= 0.05f;
        TReal			_zFar	= 10000.f;
        TReal			_fovY	= 70.f;
        TReal			_left	= 0;
        TReal			_right	= 0;
        TReal			_bottom	= 0;
        TReal			_top	= 0;
        TReal			_aspect	= 0;
        EProjectionKind	_kind = E_PROJETION_KIND_PERSPECTIVE;
        TBool			_dirty	= kTrue;
    };
}
