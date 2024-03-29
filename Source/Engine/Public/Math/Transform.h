#pragma once

#include <Base/Wrap.h>
#include <Base/Vector.h>
#include <Math/Math.h>

namespace Neowise {

    class CTransform {
    public:
        CTransform(const FVector3& translation = FVector3::zero, const FVector3& rotation = FVector3::zero, const FVector3& scale = FVector3::one);
        CTransform(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale = FVector3::one);
        explicit CTransform(const FQuaternion& rotation);
        
        CTransform createChild(const FVector3& translation = FVector3::zero, const FVector3& rotation = FVector3::zero, const FVector3& scale = FVector3::one);
        CTransform createChild(const FVector3& translation, const FQuaternion& rotation, const FVector3& scale = FVector3::one);

        CWrap<const CTransform> getParent() const {
            return _parent;
        }

        const FMatrix4& getMatrix() const;
        const FVector3& getLocalPosition() const;
        const FVector3& getLocalRotation() const;
        const FQuaternion& getLocalRotationQuat() const;
        const FVector3& getLocalScale() const;

        FVector3& localPosition();
        FVector3& localRotation();
        FQuaternion& localRotationQuat();
        FVector3& localScale();

        FVector3 getPosition() const;
        FVector3 getRotation() const;
        FQuaternion getRotationQuat() const;

        void recalculate();
    private:
        bool isDirty(const uint8 flag) const;
        void setDirty(const uint8 flag);

    private:
        FMatrix4                _modelMatrix = FMatrix4(1);

        FVector3                _localPosition = {};
        FVector3                _localRotationEuler = {};
        FQuaternion             _localRotation = {};
        FVector3                _localScale = FVector3::one;
    
        CWrap<const CTransform> _parent = nullptr;

        uint8                   _dirtyFlags = 14;
    };

}
