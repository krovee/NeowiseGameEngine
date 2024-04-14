#include <Math/Projection.h>

namespace Neowise {
    CProjection::CProjection(EProjectionKind kind, const IProjectionCreateInfoBase& createInfo) : _kind(kind) {
        switch (kind) {
            case E_PROJETION_KIND_PERSPECTIVE: setupPerspective((SProjectionPerspectiveCreateInfo)createInfo); return;
            case E_PROJECTION_KIND_ORTHOGRAPHIC: setupOrthographic((SProjectionOrthographicCreateInfo)createInfo); return;
        }
    }

    void CProjection::setNearZ(TReal value) {
        _zNear = value;
        _dirty = true;
    }

    void CProjection::setFarZ(TReal value) {
        _zFar = value;
        _dirty = true;
    }

    void CProjection::setSize(const FVec2& size) {
        _aspect = size[0] / size[1];
        _left = _top = 0;
        _right = size[0];
        _bottom = size[1];
        _dirty = true;
    }

    void CProjection::setRectSize(TReal left, TReal right, TReal top, TReal bottom) {
        _left = left;
        _right = right;
        _top = top;
        _bottom = bottom;
        _dirty = true;
    }

    void CProjection::setFovY(TReal value) {
        _fovY = value;
        _dirty = true;
    }

    CProjection::operator FMatrix4() const {
        return _mat;
    }

    void CProjection::updateRequired() {
        switch (_kind) {
            case E_PROJETION_KIND_PERSPECTIVE: {
                SProjectionPerspectiveCreateInfo info;
                info.viewportSize = { _right - _left, _bottom - _top };
                info.nearPlaneZ = _zNear;
                info.fovY = _fovY;
                setupPerspective(info);
            } break;
            case E_PROJECTION_KIND_ORTHOGRAPHIC: {
                SProjectionOrthographicCreateInfo info;
                info.left = _left;
                info.right = _right;
                info.top = _top;
                info.bottom = _bottom;
                info.nearPlaneZ = _zNear;
                info.farPlaneZ = _zFar;
                setupOrthographic(info);
            } break;
        }
        _dirty = false;
    }

    void CProjection::setupPerspective(const SProjectionPerspectiveCreateInfo& createInfo) {
        const auto aspect = createInfo.viewportSize[0] / createInfo.viewportSize[1];
        const auto range = tan(createInfo.fovY / (TReal)(2)) * createInfo.nearPlaneZ;
        const auto left = -range * aspect;
        const auto right = range * aspect;
        const auto bottom = -range;
        const auto top = range;

        if (right - left != 0) {
            _mat[0][0] = (TReal(2) * createInfo.nearPlaneZ) / (right - left);
        }
        _mat[1][1] = (TReal(2) * createInfo.nearPlaneZ) / (top - bottom);
        _mat[2][2] = TReal(-0.9999988);
        _mat[2][3] = TReal(-1);
        _mat[3][2] = TReal(-1.9999988) * createInfo.nearPlaneZ;
    }

    void CProjection::setupOrthographic(const SProjectionOrthographicCreateInfo& createInfo) {
        if (createInfo.right - createInfo.left != 0) {
            _mat[0][0] = (TReal)(2) / (createInfo.right - createInfo.left);
        }
        if (createInfo.top - createInfo.bottom != 0) {
            _mat[1][1] = (TReal)(2) / (createInfo.top - createInfo.bottom);
        }
        _mat[2][2] = -(TReal)(2) / (createInfo.farPlaneZ - createInfo.nearPlaneZ);
        _mat[3][0] = -(createInfo.right + createInfo.left) / (createInfo.right - createInfo.left);
        _mat[3][1] = -(createInfo.top + createInfo.bottom) / (createInfo.top - createInfo.bottom);
        _mat[3][2] = -(createInfo.farPlaneZ + createInfo.nearPlaneZ) / (createInfo.farPlaneZ - createInfo.nearPlaneZ);
    }

}
