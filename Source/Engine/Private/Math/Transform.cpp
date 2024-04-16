#include <Math/Transform.h>

namespace Neowise {

    enum ETransformFlags : TUint8 {
        E_TRANSFORM_LOCAL_POSITION_DIRTY    = 1 << 1, 
        E_TRANSFORM_LOCAL_ROTATION_DIRTY    = 1 << 2, 
        E_TRANSFORM_LOCAL_SCALE_DIRTY       = 1 << 3, 
    };

    TBool CTransform::isDirty(const TUint8 flag) const {
        return (_dirtyFlags & flag) == flag;
    }

    void CTransform::setDirty(const TUint8 flag) {
        _dirtyFlags |= flag;
    }

    void CTransform::resetParent(CWrap<const CTransform> parent) {
        _parent = parent;
    }

    FMatrix4 CTransform::getMatrix() const {
        return _localMatrix;
    }

    const FVector3& CTransform::getLocalPosition() const {
        return _localPosition;
    }

    FVector3 CTransform::getLocalRotationEuler() const {
        return _localRotation.euler();
    }

    const FQuaternion& CTransform::getLocalRotation() const {
        return _localRotation;
    }

    const FVector3& CTransform::getLocalScale() const {
        return _localScale;
    }

    FVector3& CTransform::localPosition() {
        setDirty(E_TRANSFORM_LOCAL_POSITION_DIRTY);
        return _localPosition;
    }

    FQuaternion& CTransform::localRotation() {
        setDirty(E_TRANSFORM_LOCAL_ROTATION_DIRTY);
        return _localRotation;
    }

    FVector3& CTransform::localScale() {
        setDirty(E_TRANSFORM_LOCAL_SCALE_DIRTY);
        return _localScale;
    }

    void CTransform::recalculate() {
        if (isDirty(E_TRANSFORM_LOCAL_SCALE_DIRTY)) {
            _localMatrix = scale(_localMatrix, _localScale);
        }

        if (isDirty(E_TRANSFORM_LOCAL_ROTATION_DIRTY)) {
            _localRotation.apply(_localMatrix);
        }

        if (isDirty(E_TRANSFORM_LOCAL_POSITION_DIRTY)) {
            _localMatrix = translate(_localMatrix, _localPosition);
        }

        if (_parent) {
            _localMatrix = _parent.unwrap().getMatrix() * _localMatrix;
        }

        _dirtyFlags = 0;
    }

    CTransform::CTransform(const FVector3& translation, const FVector3& rotation, const FVector3& scale) : _localPosition(translation), _localRotation(rotation), _localScale(scale) {
        _dirtyFlags = E_TRANSFORM_LOCAL_POSITION_DIRTY | E_TRANSFORM_LOCAL_ROTATION_DIRTY | E_TRANSFORM_LOCAL_SCALE_DIRTY;
    }

    CTransform::CTransform(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale) : _localPosition(translation), _localRotation(rotation), _localScale(scale) {
        _dirtyFlags = E_TRANSFORM_LOCAL_POSITION_DIRTY | E_TRANSFORM_LOCAL_ROTATION_DIRTY | E_TRANSFORM_LOCAL_SCALE_DIRTY;
    }

    CTransform CTransform::createChild(const FVector3& translation, const FVector3& rotation, const FVector3& scale) {
        CTransform t(translation, rotation, scale);
        t._parent = CWrap<const CTransform>(this);
        return t;
    }

    CTransform CTransform::createChild(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale) {
        CTransform t(translation, rotation, scale);
        t._parent = CWrap<const CTransform>(this);
        return t;
    }
}
