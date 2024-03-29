#include <Math/Transform.h>

namespace Neowise {

    enum ETransformFlags : uint8 {
        E_TRANSFORM_LOCAL_POSITION_DIRTY    = 1 << 1, 
        E_TRANSFORM_LOCAL_ROTATION_DIRTY    = 1 << 2, 
        E_TRANSFORM_LOCAL_SCALE_DIRTY       = 1 << 3, 
    };

    bool CTransform::isDirty(const uint8 flag) const {
        return (_dirtyFlags & flag) == flag;
    }

    void CTransform::setDirty(const uint8 flag) {
        _dirtyFlags |= flag;
    }
    

    const FMatrix4& CTransform::getMatrix() const {
        return _modelMatrix;
    }

    const FVector3& CTransform::getLocalPosition() const {
        return _localPosition;
    }

    const FVector3& CTransform::getLocalRotation() const {
        return _localRotationEuler;
    }

    const FQuaternion& CTransform::getLocalRotationQuat() const {
        return _localRotation;
    }

    const FVector3& CTransform::getLocalScale() const {
        return _localScale;
    }

    FVector3& CTransform::localPosition() {
        setDirty(E_TRANSFORM_LOCAL_POSITION_DIRTY);
        return _localPosition;
    }

    FVector3& CTransform::localRotation() {
        setDirty(E_TRANSFORM_LOCAL_ROTATION_DIRTY);
        return _localRotationEuler;
    }

    FQuaternion& CTransform::localRotationQuat() {
        setDirty(E_TRANSFORM_LOCAL_ROTATION_DIRTY);
        return _localRotation;
    }

    FVector3& CTransform::localScale() {
        setDirty(E_TRANSFORM_LOCAL_SCALE_DIRTY);
        return _localScale;
    }

    FVector3 CTransform::getPosition() const {
        if (_parent) {
            return _parent.unwrap().getPosition() * _localPosition;
        }
        
        return _localPosition;
    }

    FVector3 CTransform::getRotation() const {
        if (_parent) {
            return _parent.unwrap().getRotation() * _localPosition;
        }
        
        return _localPosition;
    }

    FQuaternion CTransform::getRotationQuat() const {
        return FQuaternion(getRotation());
    }

    void CTransform::recalculate() {
        if (isDirty(E_TRANSFORM_LOCAL_SCALE_DIRTY)) {
            _modelMatrix = scale(_modelMatrix, getRotation());
        }

        if (isDirty(E_TRANSFORM_LOCAL_ROTATION_DIRTY)) {
            _modelMatrix = rotateAxis(_modelMatrix, FVec3::right, _localRotationEuler.x);
            _modelMatrix = rotateAxis(_modelMatrix, FVec3::forward, _localRotationEuler.y);
            _modelMatrix = rotateAxis(_modelMatrix, FVec3::up, _localRotationEuler.z);
        }

        if (isDirty(E_TRANSFORM_LOCAL_POSITION_DIRTY)) {
            _modelMatrix = translate(_modelMatrix, getPosition());
        }

        _dirtyFlags = 0;
    }
}
