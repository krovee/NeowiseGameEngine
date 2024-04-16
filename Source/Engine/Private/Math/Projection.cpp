#include <Math/Projection.h>

namespace Neowise {
    CProjection::CProjection(EProjectionKind kind, const IProjectionCreateInfoBase* pCreateInfo) : _kind(kind) {
        switch (kind) {
            case E_PROJETION_KIND_PERSPECTIVE: setupPerspective((SProjectionPerspectiveCreateInfo*)pCreateInfo); return;
            case E_PROJECTION_KIND_ORTHOGRAPHIC: setupOrthographic((SProjectionOrthographicCreateInfo*)pCreateInfo); return;
        }
    }

    void CProjection::setNearZ(TReal value) {
        _zNear = value;
        _dirty = kTrue;
    }

    void CProjection::setFarZ(TReal value) {
        _zFar = value;
        _dirty = kTrue;
    }

    void CProjection::setSize(const FVec2& size) {
        _aspect = size[0] / size[1];
        _left = _top = 0;
        _right = size[0];
        _bottom = size[1];
        _dirty = kTrue;
    }

    void CProjection::setRectSize(TReal left, TReal right, TReal top, TReal bottom) {
        _left = left;
        _right = right;
        _top = top;
        _bottom = bottom;
        _dirty = kTrue;
    }

    void CProjection::setFovY(TReal value) {
        _fovY = value;
        _dirty = kTrue;
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
                setupPerspective(&info);
            } break;
            case E_PROJECTION_KIND_ORTHOGRAPHIC: {
                SProjectionOrthographicCreateInfo info;
                info.left = _left;
                info.right = _right;
                info.top = _top;
                info.bottom = _bottom;
                info.nearPlaneZ = _zNear;
                info.farPlaneZ = _zFar;
                setupOrthographic(&info);
            } break;
        }
        _dirty = kFalse;
    }

    void CProjection::setupPerspective(const SProjectionPerspectiveCreateInfo* pCreateInfo) {
        const auto aspect = pCreateInfo->viewportSize[0] / pCreateInfo->viewportSize[1];
        const auto range = tan(pCreateInfo->fovY / (TReal)(2)) * pCreateInfo->nearPlaneZ;
        const auto left = -range * aspect;
        const auto right = range * aspect;
        const auto bottom = -range;
        const auto top = range;

        if (right - left != 0) {
            _mat[0][0] = (TReal(2) * pCreateInfo->nearPlaneZ) / (right - left);
        }
        _mat[1][1] = (TReal(2) * pCreateInfo->nearPlaneZ) / (top - bottom);
        _mat[2][2] = TReal(-0.9999988);
        _mat[2][3] = TReal(-1);
        _mat[3][2] = TReal(-1.9999988) * pCreateInfo->nearPlaneZ;
    }

    void CProjection::setupOrthographic(const SProjectionOrthographicCreateInfo* pCreateInfo) {
        if (pCreateInfo->right - pCreateInfo->left != 0) {
            _mat[0][0] = (TReal)(2) / (pCreateInfo->right - pCreateInfo->left);
        }
        if (pCreateInfo->top - pCreateInfo->bottom != 0) {
            _mat[1][1] = (TReal)(2) / (pCreateInfo->top - pCreateInfo->bottom);
        }
        _mat[2][2] = -(TReal)(2) / (pCreateInfo->farPlaneZ - pCreateInfo->nearPlaneZ);
        _mat[3][0] = -(pCreateInfo->right + pCreateInfo->left) / (pCreateInfo->right - pCreateInfo->left);
        _mat[3][1] = -(pCreateInfo->top + pCreateInfo->bottom) / (pCreateInfo->top - pCreateInfo->bottom);
        _mat[3][2] = -(pCreateInfo->farPlaneZ + pCreateInfo->nearPlaneZ) / (pCreateInfo->farPlaneZ - pCreateInfo->nearPlaneZ);
    }

}
